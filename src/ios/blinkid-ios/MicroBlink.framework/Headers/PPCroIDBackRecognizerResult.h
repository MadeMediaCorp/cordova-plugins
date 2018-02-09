//
//  PPCroIDBackRecognizerResult.h
//  BlinkIdFramework
//
//  Created by Boris Trubic on 05/05/16.
//  Copyright © 2016 MicroBlink Ltd. All rights reserved.
//

#import "PPMrtdRecognizerResult.h"

/**
 * Result of scanning with Croatian ID Back side recognizer
 */
PP_CLASS_AVAILABLE_IOS(6.0)
@interface PPCroIDBackRecognizerResult : PPMrtdRecognizerResult

/**
 * The address of the Croatian ID owner.
 */
@property (nonatomic, readonly, nullable) NSString *address;

/**
 * The issuing authority of Croatian ID.
 */
@property (nonatomic, readonly, nullable) NSString *issuingAuthority;

/**
 * The document date of issue of the Croatian ID in DD.MM.yyyy format.
 */
@property (nonatomic, readonly, nullable) NSString *rawDocumentDateOfIssue;

/**
 * The document date of issue of the Croatian ID.
 */
@property (nonatomic, readonly, nullable) NSDate *documentDateOfIssue;

/**
 * Check if date of expiry is permanent on the Croatian ID.
 */
@property (nonatomic, readonly) BOOL isDocumentDateOfExpiryPermanent;

@end
