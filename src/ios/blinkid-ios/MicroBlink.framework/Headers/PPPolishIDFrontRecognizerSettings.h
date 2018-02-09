//
//  PPPolishIDFrontRecognizerSettings.h
//  MicroBlinkDev
//
//  Created by Jura Skrlec on 19/10/2017.
//

#import "PPRecognizerSettings.h"


NS_ASSUME_NONNULL_BEGIN

/**
 * Settings class for configuring Polish Front ID Recognizer.
 *
 * Polish Front ID recognizer is used for scanning front side of Polish ID.
 */
PP_CLASS_AVAILABLE_IOS(6.0)
@interface PPPolishIDFrontRecognizerSettings : PPRecognizerSettings

/**
 * Name of the image sent to didOutputMetadata method of scanDelegate object that contains face.
 * This image will be sent to scan delegate during recognition process if displaying of face image
 * is enabled via displayFaceImage property and receiving of dewarpedImage in MetadataSettings is enabled.
 */
+ (NSString *)ID_FACE;

/**
 * Name of the image sent to didOutputMetadata method of scanDelegate object that contains full document.
 * This image will be sent to scan delegate during recognition process if displaying of full document image
 * is enabled via displayFullDocumentImage property and receiving of dewarpedImage in MetadataSettings is enabled.
 */
+ (NSString *)FULL_DOCUMENT_IMAGE;

/**
 *  Defines if sex of Polish ID owner should be extracted
 *
 *  Default: YES
 */
@property (nonatomic, assign) BOOL extractSex;

/**
 * Defines if citizenship of Polish ID owner should be extracted
 *
 * Default: YES
 */
@property (nonatomic, assign) BOOL extractLastName;

/**
 * Defines if date of birth of Polish ID owner should be extracted
 *
 * Default: YES
 */
@property (nonatomic, assign) BOOL extractFirstName;

/**
 * Defines if date of expiry should be extracted from Polish ID
 *
 * Default: YES
 */
@property (nonatomic, assign) BOOL extractFamilyName;

/**
 * Defines if date of expiry should be extracted from Polish ID
 *
 * Default: YES
 */
@property (nonatomic, assign) BOOL extractParentsName;

/**
 * Defines if date of expiry should be extracted from Polish ID
 *
 * Default: YES
 */
@property (nonatomic, assign) BOOL extractDateOfBirth;

/**
 * Sets whether face image from ID card should be sent to didOutputMetadata method of scanDelegate object.
 * If you want to recieve this image, be sure to enable dewarpedImage in MetadataSettings.
 *
 * Default: NO
 */
@property (nonatomic, assign) BOOL displayFaceImage;

/**
 * Sets whether full document image of ID card should be sent to didOutputMetadata method of scanDelegate object.
 * If you want to recieve this image, be sure to enable dewarpedImage in MetadataSettings.
 *
 * Default: NO
 */
@property (nonatomic, assign) BOOL displayFullDocumentImage;

/**
 * Defines if glare detection should be turned on/off for front side of Polish IDs.
 *
 * Default: YES
 */
@property (nonatomic, assign) BOOL detectGlare;

@end

NS_ASSUME_NONNULL_END
