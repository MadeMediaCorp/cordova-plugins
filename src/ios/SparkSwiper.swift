//
//  SparkSwiperManager.swift
//  onboard
//
//  Created by Nijun Wei on 2017-08-08.
//  Copyright © 2017 Made Media Inc. All rights reserved.
//

import Foundation
import AVFoundation

@objc(SparkSwiper) class SparkSwiper: CDVPlugin {
    func collectCard(_ command: CDVInvokedUrlCommand) {
        let callbackId = command.callbackId!
        let nc = NotificationCenter.default
        let listenerName = "swiperMessage"
        nc.post(name: NSNotification.Name(rawValue: listenerName), object: nil, userInfo:["data": "Accessing the swiper. Please wait...", "status": "message"])
        DispatchQueue.global(qos: DispatchQoS.QoSClass.default).async {
            let swiper = SwiperManager.sharedManager
            if swiper.start() {
                if !swiper.isTampered() {
                    DispatchQueue.main.async {
                        nc.post(name: NSNotification.Name(rawValue: listenerName), object: nil, userInfo:["data": "Please swipe your card now...", "status": "success"])
                    }
                    do {
                        let card = try swiper.waitForCard(10.0)
                        if card.cardType == ASCCardTypeMagnetic {
                            DispatchQueue.main.async {
                                nc.post(name: NSNotification.Name(rawValue: listenerName), object: nil, userInfo:["data": "Card detected.", "status": "success"])
                            }
                            guard let encryptedData = swiper.msGetEncryptedCardData() else {
                                DispatchQueue.main.async {
                                    self.execFailureCallback(callbackId, error: "Error processing card data.")
                                }
                                return
                            }
                            var encrypted = String(format: "%@", encryptedData as CVarArg)
                            encrypted = encrypted.replacingOccurrences(of: " ", with: "")
                            encrypted = encrypted.replacingOccurrences(of: "<", with: "")
                            encrypted = encrypted.replacingOccurrences(of: ">", with: "")
                            guard let maskedData = swiper.msGetFinancialCardMaskedData() else {
                                DispatchQueue.main.async {
                                    self.execFailureCallback(callbackId, error: "Failed to process card data. Please try again.")
                                }
                                return
                            }
                            
                            let monthString = "\(maskedData.expirationMonth)"
                            let expiryMonth = monthString.characters.count == 1 ? "0" + monthString : monthString
                            let cardDictionary = ["name": maskedData.name,
                                                  "number": maskedData.number,
                                                  "expiry": "\(expiryMonth)/\(maskedData.expirationYear)",
                                "cvv": "",
                                "encrypted": encrypted] as [String: String]
                            var jsonString : String?
                            do {
                                let jsonData = try JSONSerialization.data(withJSONObject: cardDictionary, options: JSONSerialization.WritingOptions())
                                jsonString = (String(data: jsonData, encoding: .utf8)?.replacingOccurrences(of: "\\/", with: "/"))
                            } catch _ {
                            }
                            let pluginResult = CDVPluginResult(status: CDVCommandStatus_OK, messageAs: jsonString ?? "")
                            self.commandDelegate.send(pluginResult, callbackId: callbackId)
                        } else if card.cardType == ASCCardTypeSmartCard {
                            DispatchQueue.main.async {
                                self.execFailureCallback(callbackId, error: "Chip cards not supported. Please try again.")
                            }
                        }
                    } catch let error as NSError {
                        DispatchQueue.main.async {
                            if error.code == 3 {
                                self.execFailureCallback(callbackId, error: "Swiper battery low")
                            } else {
                                self.execFailureCallback(callbackId, error: "Could not detect card. Please try again.")
                            }
                        }
                    }
                } else {
                    DispatchQueue.main.async {
                        self.execFailureCallback(callbackId, error: "Swiper tampered. Please contact your manager!")
                    }
                }
            } else {
                DispatchQueue.main.async {
                    self.execFailureCallback(callbackId, error: "Can not access swiper. Please try again.")
                }
            }
            swiper.stop()
        }
    }
    fileprivate func execFailureCallback(_ callbackId: String, error: String) {
        NotificationCenter.default.post(name: NSNotification.Name(rawValue: "swiperMessage"), object: nil, userInfo:["status": "error", "data": error])
        let pluginResult = CDVPluginResult(status: CDVCommandStatus_ERROR)
        self.commandDelegate.send(pluginResult, callbackId: callbackId)
    }
    func turnOff(_ command: CDVInvokedUrlCommand) {
        print("turning swiper off");
        SwiperManager.sharedManager.turnOff()
        self.commandDelegate.send(CDVPluginResult(status: CDVCommandStatus_OK), callbackId: command.callbackId!)
    }
    func reset(_ command: CDVInvokedUrlCommand) {
        print("Reseting swiper");
        SwiperManager.sharedManager.reset()
        self.commandDelegate.send(CDVPluginResult(status: CDVCommandStatus_OK), callbackId: command.callbackId!)
    }
    func prepareSwiper(_ command: CDVInvokedUrlCommand) {
        print("Preparing swiper");
        SwiperManager.sharedManager.prepareSessionForSwiper()
        self.commandDelegate.send(CDVPluginResult(status: CDVCommandStatus_OK), callbackId: command.callbackId!)
    }
    func stopWaitingForCard(_ command: CDVInvokedUrlCommand) {
        print("Stop waiting for card");
        SwiperManager.sharedManager.stopWaitingForCard()
        self.commandDelegate.send(CDVPluginResult(status: CDVCommandStatus_OK), callbackId: command.callbackId!)
    }
}
class SwiperManager: NSObject, AudioReaderDelegate {
    static let sharedManager = SwiperManager()
    fileprivate var swiper: AudioSmartCardReader
    fileprivate var waitingForCard = false

    override fileprivate init() {
        
        swiper = AudioSmartCardReader.sharedDevice() as! AudioSmartCardReader
        
        super.init()
        
        swiper.delegate = self
    }

    func prepareSessionForSwiper() {
        let session = AVAudioSession.sharedInstance()
        if let inputs = session.availableInputs {
            for port in inputs {
                if port.portType == AVAudioSessionPortHeadsetMic {
                    do {
                        try session.setCategory(AVAudioSessionCategoryPlayAndRecord)
                        try session.setActive(true)
                        try session.setPreferredInput(port)
                    } catch _ {
                        self.log("ERROR: Failed to prepare the audio session for the swiper.")
                    }
                }
            }
        }
    }

    func turnOff() {
        if swiper.isPluggedIn() && swiper.isPoweredOn {
            swiper.powerOff()
        }
    }
    
    enum CardSwiperError: Error {
        case canNotAccess
        case tampered
        case timeout
        case batteryLow
    }

    func start() -> Bool {
        prepareSessionForSwiper()
        
        if !swiper.power(on: nil) {
            reset()
            swiper.power(on: nil)
        }
        
        return swiper.isPoweredOn
    }
    
    func isTampered() -> Bool {
        do {
            let keys = try swiper.emsrGetKeysInfo()
            if keys.tampered {
                return true
            }
        } catch { }
        return false
    }
    func stop() {
        swiper.powerOff()
    }
    func reset() {
        swiper.forceReinit()
    }
    func waitForCard(_ time: TimeInterval) throws -> ASCCardInfo {
        
        var card: ASCCardInfo?
        
        swiper.setMagneticCardModeEncryption(ASCEncryptionTypeIDTECH, track1Mode: ASCTrackReadModeAllowed, track2Mode: ASCTrackReadModeAllowed, track3Mode: ASCTrackReadModeAllowed)
        swiper.setMagneticCardMaskModeShowExpiration(true, showServiceCode: true, unmaskedDigitsAtStart: 6, unmaskedDigitsAtEnd: 4)
        
        waitingForCard = true
        self.log("Waiting for a card swipe...")
        do {
            card = try swiper.wait(forCard: time)
            waitingForCard = false
        } catch let error as NSError {
            waitingForCard = false
            self.log("\(error)")
            if (error.code == ASCStatus_STATUS_BATTERY_LOW) {
                throw CardSwiperError.batteryLow
            }
        }
        
        if (card == nil) {
            throw CardSwiperError.timeout
        }
        
        self.log("Card detected.")
        
        return card!
    }
    func stopWaitingForCard() {
        if waitingForCard {
            swiper.waitForCardCancel()
            waitingForCard = false
        }
    }
    func msGetEncryptedCardData() -> Data? {
        do {
            return try swiper.msGetEncryptedCardData()
        } catch { }
        return nil
    }
    
    func msGetFinancialCardMaskedData() -> ASCFinancialCardInfo? {
        do {
            return try swiper.msGetFinancialCardMaskedData()
        } catch { }
        return nil
    }
    
    func readerDidPlugIn(_ audioReader: AudioSmartCardReader!) {
        self.log("Swiper plugged.")
    }
    
    func readerDidUnplug(_ audioReader: AudioSmartCardReader!) {
        self.log("Swiper unplugged.")
    }
    fileprivate func log(_ message: String) {
        print("SparkSwiperManager: " + message)
    }
}
