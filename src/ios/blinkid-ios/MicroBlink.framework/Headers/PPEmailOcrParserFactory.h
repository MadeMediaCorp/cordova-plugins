//
//  PPEmailParserFactory.h
//  PhotoPayFramework
//
//  Created by Dino on 14/12/15.
//  Copyright © 2015 MicroBlink Ltd. All rights reserved.
//

#import "PPOcrParserFactory.h"

/**
 *  Parses email addresses.
 */
PP_CLASS_AVAILABLE_IOS(6.0)
@interface PPEmailOcrParserFactory : PPOcrParserFactory

/**
 * Creates parser instance with default parametars.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end
