//
//  SparkAudioManager.swift
//  Spark
//
//  Created by Nijun Wei on 2017-08-07.
//
//

import Foundation
import AVFoundation

@objc(SparkAudio) class SparkAudio: CDVPlugin {
    func prepareRecording(_ command: CDVInvokedUrlCommand) {
        let success = SparkAudioManager.sharedManager.prepareSessionForRecording()
        sendResult(success, callbackId: command.callbackId)
    }
    func startRecording(_ command: CDVInvokedUrlCommand) {
        print("SparkAudio: startVoiceRecording")
        
        // Start recording session below
        if let filePath = SparkAudioManager.sharedManager.startRecording() {
            print("SparkAudio: filePath - \(filePath)")
            // Return success
            sendResult(true, callbackId: command.callbackId, string: filePath)
        } else {
            sendResult(false, callbackId: command.callbackId, string: "")
        }
    }
    func stopRecording(_ command: CDVInvokedUrlCommand) {
        SparkAudioManager.sharedManager.stopRecording()
        sendResult(true, callbackId: command.callbackId)
    }
    func pauseRecording(_ command: CDVInvokedUrlCommand) {
        SparkAudioManager.sharedManager.pauseRecording()
        sendResult(true, callbackId: command.callbackId)
    }
    func resumeRecording(_ command: CDVInvokedUrlCommand) {
        SparkAudioManager.sharedManager.resumeRecording()
        sendResult(true, callbackId: command.callbackId)
    }
    func isPaused(_ command: CDVInvokedUrlCommand) {
        let paused = SparkAudioManager.sharedManager.isPaused()
        sendResult(true, callbackId: command.callbackId, bool: paused)
    }
    func isRecording(_ command: CDVInvokedUrlCommand) {
        let recording = SparkAudioManager.sharedManager.isRecording()
        sendResult(true, callbackId: command.callbackId, bool: recording)
    }
    func closeSession(_ command: CDVInvokedUrlCommand) {
        SparkAudioManager.sharedManager.closeSession()
        sendResult(true, callbackId: command.callbackId)
    }
    
    // Speaker
    func prepareSpeaker(_ command: CDVInvokedUrlCommand) {
        let success = SparkAudioManager.sharedManager.prepareSessionForSpeakerUse()
        sendResult(success, callbackId: command.callbackId)
    }
    func speakerUseEnded(_ command: CDVInvokedUrlCommand) {
        SparkAudioManager.sharedManager.speakerUseEnded()
        sendResult(true, callbackId: command.callbackId)
    }
    
    // Helper functions
    fileprivate func sendResult(_ success: Bool, callbackId: String) {
        let pluginResult = CDVPluginResult(status: success ? CDVCommandStatus_OK : CDVCommandStatus_ERROR)
        self.commandDelegate.send(pluginResult, callbackId: callbackId)
    }
    fileprivate func sendResult(_ success: Bool, callbackId: String, bool: Bool) {
        if success {
            let pluginResult = CDVPluginResult(status: CDVCommandStatus_OK , messageAs: bool)
            self.commandDelegate.send(pluginResult, callbackId: callbackId)
        } else {
            sendResult(false, callbackId: callbackId)
        }
    }
    fileprivate func sendResult(_ success: Bool, callbackId: String, string: String) {
        let pluginResult = CDVPluginResult(status: success ? CDVCommandStatus_OK : CDVCommandStatus_ERROR, messageAs: string)
        self.commandDelegate.send(pluginResult, callbackId: callbackId)
    }
}

class SparkAudioManager: NSObject {
    
    fileprivate var session: AVAudioSession
    fileprivate var recorder: AVAudioRecorder?
    fileprivate var paused = false
    
    static let sharedManager = SparkAudioManager()
    
    override fileprivate init() {
        
        session = AVAudioSession.sharedInstance()
        
        super.init()

        let nc = NotificationCenter.default
        nc.addObserver(self, selector: #selector(SparkAudioManager.routeChanged(_:)), name: NSNotification.Name.AVAudioSessionRouteChange, object: nil)

        let _ = self.prepareSessionForRecording()
    }
    // Route change notification
    func routeChanged(_ notification: Notification) {
        log("Route change detected.")
        let reason = (notification as NSNotification).userInfo![AVAudioSessionRouteChangeReasonKey] as! UInt
        if reason == AVAudioSessionRouteChangeReason.newDeviceAvailable.rawValue && self.isRecording() {
            // User may have (re)plugged the swiper. Pause the recording and send a reset request to the SDK.
            log("Sending RouteChanged notification to js")
            NotificationCenter.default.post(name: NSNotification.Name(rawValue: "AppRouteChanged"), object: nil, userInfo:nil)
        }
    }
    
    func prepareSessionForRecording() -> Bool {
        if let inputs = session.availableInputs {
            for port in inputs {
                if port.portType == AVAudioSessionPortBuiltInMic {
                    do {
                        try session.setCategory(AVAudioSessionCategoryPlayAndRecord)
                        try session.setActive(true)
                        try session.setPreferredInput(port)
                    } catch _ {
                        self.log("ERROR: Failed to prepare the audio session for recording.")
                    }
                    
                    return true
                }
            }
        }
        self.log("ERROR: Internal microphone port not available.")
        return false
    }
    
    func startRecording() -> String? {
        
        guard prepareSessionForRecording() else {
            return nil
        }
        
        let tmppath = NSTemporaryDirectory()
        let filePath = tmppath + "voice.mp4"
        let audioFileURL = URL(fileURLWithPath: filePath)
        
        let settings: [String: AnyObject] = ["AVFormatIDKey": NSNumber(value: kAudioFormatMPEG4AAC as UInt32),
                                             "AVSampleRateKey" : NSNumber(value: 8000.0 as Float),
                                             "AVNumberOfChannelsKey" : NSNumber(value: 1 as UInt32),
                                             "AVEncoderAudioQualityKey" : NSNumber(value: 0 as UInt32)]
        
        do {
            recorder = try AVAudioRecorder(url: audioFileURL, settings: settings)
        } catch _ {
            self.log("ERROR: Failed to initialize recorder object.")
            return nil
        }
        
        if recorder!.record() {
            self.log("Starting recording.")
            return filePath
        }
        
        self.log("ERROR: Failed to initialize recorder object.")
        return nil
    }
    func stopRecording() {
        if self.isRecording() {
            log("Stopping recording.")
            recorder!.stop()
            recorder = nil
        }
    }
    func pauseRecording() {
        if self.isRecording() {
            log("Pausing recording.")
            recorder!.pause()
            paused = true
        }
    }
    
    func resumeRecording() {
        if let _ = recorder {
            log("Resuming recording.")
            recorder!.record()
            paused = false
        }
    }
    
    
    func isPaused() -> Bool {
        return paused
    }
    func isRecording() -> Bool {
        if let _ = recorder {
            if recorder!.isRecording {
                return true
            }
        }
        return false
    }
    
    // Speaker
    func prepareSessionForSpeakerUse() -> Bool {
        
        do {
            try session.overrideOutputAudioPort(.speaker)
        } catch {
            return false
        }
        
        return true
    }
    func speakerUseEnded() {
        do {
            try session.overrideOutputAudioPort(.none)
        } catch {}
    }
    
    func closeSession() {
        
        stopRecording()
        
        DispatchQueue.main.asyncAfter(deadline: .now() + 0.5) {
            self.deactivateSession()
        }
    }
    
    func deactivateSession() {
        self.log("Deactivating the audio session.")
        do {
            try AVAudioSession.sharedInstance().setActive(false, with: .notifyOthersOnDeactivation)
        } catch {
            self.log("ERROR: Failed to deactivate the audio session.")
        }
    }
    
    fileprivate func log(_ message: String) {
        print("SparkAudioManager: " + message)
    }
    
}
