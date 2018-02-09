//
//  ImageFetcher.swift
//  Spark
//
//  Created by Nijun Wei on 2017-11-24.
//
//

import Foundation

@objc(ImageFetcher) class ImageFetcher: CDVPlugin {
    func download(_ command: CDVInvokedUrlCommand) {
        print("ImageFetcher downloading")
        DispatchQueue.global(qos: DispatchQoS.QoSClass.default).async {
            let callbackId = command.callbackId!
            if command.arguments.count > 1 {
                let images = command.arguments[0]
                let campaign = (command.arguments[1] as? String) ?? "fallback"
                if let json = images as? [[String: Any]] {
                    let resp = self.start(array: json, campaign: campaign)
                    self.commandDelegate.send(CDVPluginResult(status: CDVCommandStatus_OK, messageAs: resp), callbackId: callbackId)
                } else if let string = images as? String {
                    if let array = self.stringToArray(string) as? [[String: Any]] {
                        let resp = self.start(array: array, campaign: campaign)
                        self.commandDelegate.send(CDVPluginResult(status: CDVCommandStatus_OK, messageAs: resp), callbackId: callbackId)
                    } else {
                        self.commandDelegate.send(CDVPluginResult(status: CDVCommandStatus_ERROR, messageAs: "Failed to convert images string to array"), callbackId: callbackId)
                    }
                }
            } else {
                self.commandDelegate.send(CDVPluginResult(status: CDVCommandStatus_ERROR, messageAs: "Lack of one or more parameters"), callbackId: callbackId)
            }
        }
    }
    func start(array: [[String: Any]], campaign: String) -> String {
        // Create campaign folder
        let root = URL(fileURLWithPath: NSSearchPathForDirectoriesInDomains(.documentDirectory, .userDomainMask, true)[0])
        let directoryPath = root.appendingPathComponent(campaign)
        if !FileManager.default.fileExists(atPath: directoryPath.path) {
            do {
                try FileManager.default.createDirectory(at: directoryPath, withIntermediateDirectories: true, attributes: nil)
            } catch {
                return arrayToString(array) ?? ""
            }
        }
        let group = DispatchGroup()
        var resp = array
        for i in 0..<(array.count) {
            var image = array[i]
            if let string = image["img"] as? String {
                let name = self.trimToFit(regex: "[^\\w\\s]", string: (image["value"] as? String)) ?? String(i)
                let filePath = directoryPath.appendingPathComponent(name)
                resp[i]["value"] = name
                if let url = URL(string: string) {
                    group.enter()
                    downloadAndSave(url: url, filePath: filePath, completion: { (data) in
                        group.leave()
                    })
                }
            }
        }
        group.wait()
        if let newString = arrayToString(resp) {
            return newString
        } else {
            return ""
        }
    }
    func trimToFit(regex: String, string: String?) -> String? {
        if (string == nil) {
            return nil
        }
        do {
            let regex = try NSRegularExpression(pattern: regex)
            return regex.stringByReplacingMatches(in: string!, range: NSMakeRange(0, string!.characters.count), withTemplate: "")
        } catch {
            return nil
        }
    }
    func downloadAndSave(url: URL, filePath: URL, completion: @escaping (_ data: Data?) -> Void) {
        URLSession.shared.dataTask(with: url, completionHandler: { (data, response, error) in
            if (data != nil) {
                do {
                   try data!.write(to: filePath, options: [.atomic])
                } catch {
                    print("error when writting data to \(filePath)")
                }
            }
            completion(data)
        }).resume()
    }
    func stringToArray(_ string: String) -> [Any]? {
        if let data = string.data(using: .utf8) {
            do {
                let json: Any = try JSONSerialization.jsonObject(with: data, options: .allowFragments)
                if let jsonArray = json as? Array<Any> {
                    return jsonArray
                } else {
                    print("JSON string doesn't seem to represent an array")
                }
            } catch _ {
                print("String cannot be serialized into proper JSON")
            }
        } else {
            print("Cannot create Data from given optionsJSON string")
        }
        return nil
    }
    func arrayToString(_ array: [[String: Any]]) -> String? {
        do {
            let jsonData = try JSONSerialization.data(withJSONObject: array, options: JSONSerialization.WritingOptions())
            return String(data: jsonData, encoding: .utf8)?.replacingOccurrences(of: "\\/", with: "/")
        } catch _ {
        }
        return nil
    }
}
