//
//  PPAustraliaDLFrontRecognizerSettings.h
//  MicroBlinkDev
//
//  Created by Jura Skrlec on 06/09/2017.
//
//

#import "PPRecognizerSettings.h"


NS_ASSUME_NONNULL_BEGIN

/**
 * Settings class for configuring Asutralian Front DL Recognizer.
 *
 * Australian Front ID recognizer is used for scanning front side of Australian DL. It always extracts
 * identity card number, first and last name of ID holder while extracting other elements is optional.
 */
PP_CLASS_AVAILABLE_IOS(6.0)
@interface PPAustraliaDLFrontRecognizerSettings : PPRecognizerSettings

/**
 * Name of the image sent to didOutputMetadata method of scanDelegate object that contains face.
 * This image will be sent to scan delegate during recognition process if displaying of face image
 * is enabled via displayFaceImage property and receiving of dewarpedImage in MetadataSettings is enabled.
 */
+ (NSString *)ID_FACE;

/**
 * Name of the image sent to didOutputMetadata method of scanDelegate object that contains signature.
 * This image will be sent to scan delegate during recognition process if displaying of face image
 * is enabled via displaySignatureImage property and receiving of dewarpedImage in MetadataSettings is enabled.
 */
+ (NSString *)ID_SIGNATURE;

/**
 * Name of the image sent to didOutputMetadata method of scanDelegate object that contains full document.
 * This image will be sent to scan delegate during recognition process if displaying of full document image
 * is enabled via displayFullDocumentImage property and receiving of dewarpedImage in MetadataSettings is enabled.
 */
+ (NSString *)FULL_DOCUMENT_IMAGE;

/**
 *  Defines if sex of Australian DL owner should be extracted
 *
 *  Default: YES
 */
@property (nonatomic, assign) BOOL extractAddress;

/**
 * Defines if citizenship of Australian DL owner should be extracted
 *
 * Default: YES
 */
@property (nonatomic, assign) BOOL extractLicenceNumber;

/**
 * Defines if date of birth of Australian DL owner should be extracted
 *
 * Default: YES
 */
@property (nonatomic, assign) BOOL extractDateOfBirth;

/**
 * Defines if date of expiry should be extracted from Australian DL
 *
 * Default: YES
 */
@property (nonatomic, assign) BOOL extractDateOfExpiry;

/**
 * Sets whether face image from ID card should be sent to didOutputMetadata method of scanDelegate object.
 * If you want to recieve this image, be sure to enable dewarpedImage in MetadataSettings.
 *
 * Default: NO
 */
@property (nonatomic, assign) BOOL displayFaceImage;

/**
 * Sets whether signature image from ID card should be sent to didOutputMetadata method of scanDelegate object.
 * If you want to recieve this image, be sure to enable dewarpedImage in MetadataSettings.
 *
 * Default: NO
 */
@property (nonatomic, assign) BOOL displaySignatureImage;

/**
 * Sets whether full document image of ID card should be sent to didOutputMetadata method of scanDelegate object.
 * If you want to recieve this image, be sure to enable dewarpedImage in MetadataSettings.
 *
 * Default: NO
 */
@property (nonatomic, assign) BOOL displayFullDocumentImage;

/**
 * Property got setting DPI for full document images
 *
 * Default: 250.0
 */
@property (nonatomic, assign) NSUInteger fullDocumentImageDPI;

@end

NS_ASSUME_NONNULL_END
