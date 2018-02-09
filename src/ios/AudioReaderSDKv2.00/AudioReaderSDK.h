/** @defgroup G_AUDIOREADER AudioReader SDK
 Provides access to audio reader functions for working with SmartCard.
 In order to use AudioReaderSDK in your program, several steps have to be performed:
 - Include AudioReaderSDK.h and libAudioReaderSDK.a in your project.
 - Go to Frameworks and add AudioToolbox, MediaPlayer and AVFoundation frameworks
 @{
 */

#import <Foundation/Foundation.h>

#define getFinancialCardMaskedData msGetFinancialCardMaskedData

/**
 * The class that represents card status response.
 */
@interface CardStatusResponse : NSObject
#define CARD_AVAILABLE 0x100
#define CARD_POWERED 0x200
#define CARD_UNKNOWN_PROTOCOL 0x10

/**
 * Definition of message processing result.
 */
#define MESSAGE_RESULT_OK 0x0000
#define MESSAGE_RESULT_CANCELLED 0x0001
#define MESSAGE_RESULT_CARD_BLOCKED 0x0002
#define MESSAGE_RESULT_CARD_MISSING 0x0003
#define MESSAGE_RESULT_CHIP_ERROR 0x0004
#define MESSAGE_RESULT_DATA_ERROR 0x0005
#define MESSAGE_RESULT_EMPTY_LIST 0x0006
#define MESSAGE_RESULT_GPO6985 0x0007
#define MESSAGE_RESULT_MISSING_DATA 0x0008
#define MESSAGE_RESULT_NO_CARD_INSERTED 0x0009
#define MESSAGE_RESULT_NO_PROFILE 0x000A
#define MESSAGE_RESULT_NOT_ACCEPTED 0x000B
#define MESSAGE_RESULT_TIME_OUT 0x000C
#define MESSAGE_RESULT_ABORTED 0x000D
#define MESSAGE_RESULT_FALLBACK_PROHIBITED 0x000E
#define MESSAGE_RESULT_CONFIGURATION_ERROR 0x000F
#define MESSAGE_RESULT_EMV_LIB_ERROR 0x8001
#define MESSAGE_RESULT_FLOW_CONTROL 0x8002
#define MESSAGE_RESULT_INTERNAL_ERROR 0x8003
#define MESSAGE_RESULT_RESELECT 0x8004
#define MESSAGE_RESULT_SECURITY 0x8005
#define MESSAGE_RESULT_INPUT_DATA_ERROR 0x8006
#define MESSAGE_RESULT_OUT_OF_MEMORY 0x8007

/**
 * Processing result.
 */
@property (assign) int result;

/**
 * Card status.
 */
@property (assign) int status;

/**
 * Card protocol - 0 for T0, 1 for T1.
 */
@property (assign) int protocol;

/**
 * Returns card availability
 */
@property (readonly) bool cardAvailable;
/**
 * Returns if card is powered
 */
@property (readonly) bool cardPowered;
/**
 * Returns true if card protocol detection failed
 */
@property (readonly) bool cardUnknownProtocol;

@end

/**
 Charging state
 */
typedef enum {
    /**
     Battery is currently charging
     */
    ASCChargingCharging=0,
    /**
     Battery is discharging
     */
    ASCChargingNotCharging=1,
    /**
     Charge operation completed
     */
    ASCChargingDone=2,
} ASCChargingState;

/**
 Card type
 */
typedef enum {
    /**
     Magnetic card
     */
    ASCCardTypeMagnetic=0,
    /**
     Smart Card
     */
    ASCCardTypeSmartCard=1,
    /**
     RF Card
     */
    ASCCardTypeRF=2,
} ASCCardType;

/**
 * The class that represents smartcard reset response
 */
@interface CardResetResponse : CardStatusResponse

/**
 * Answer To Reset block
 */
@property (copy) NSData *atr;

@end

#ifndef STRUCTURES_DEFINED
#define STRUCTURES_DEFINED

typedef enum {
	BAR_EX_ALL=0,
	BAR_EX_UPCA,
	BAR_EX_CODABAR,
	BAR_EX_CODE25_NI2OF5,
	BAR_EX_CODE25_I2OF5,
	BAR_EX_CODE39,
	BAR_EX_CODE93,
	BAR_EX_CODE128,
	BAR_EX_CODE11,
	BAR_EX_CPCBINARY,
	BAR_EX_DUN14,
	BAR_EX_EAN2,
	BAR_EX_EAN5,
	BAR_EX_EAN8,
	BAR_EX_EAN13,
	BAR_EX_EAN128,
	BAR_EX_GS1DATABAR,
	BAR_EX_ITF14,
	BAR_EX_LATENT_IMAGE,
	BAR_EX_PHARMACODE,
	BAR_EX_PLANET,
	BAR_EX_POSTNET,
	BAR_EX_INTELLIGENT_MAIL,
	BAR_EX_MSI_PLESSEY,
	BAR_EX_POSTBAR,
	BAR_EX_RM4SCC,
	BAR_EX_TELEPEN,
	BAR_EX_UK_PLESSEY,
	BAR_EX_PDF417,
	BAR_EX_MICROPDF417,
	BAR_EX_DATAMATRIX,
	BAR_EX_AZTEK,
	BAR_EX_QRCODE,
	BAR_EX_MAXICODE,
	BAR_EX_RESERVED1,
	BAR_EX_RESERVED2,
	BAR_EX_RESERVED3,
	BAR_EX_RESERVED4,
	BAR_EX_RESERVED5,
	BAR_EX_UPCA_2,
	BAR_EX_UPCA_5,
	BAR_EX_UPCE,
	BAR_EX_UPCE_2,
	BAR_EX_UPCE_5,
	BAR_EX_EAN13_2,
	BAR_EX_EAN13_5,
	BAR_EX_EAN8_2,
	BAR_EX_EAN8_5,
	BAR_EX_CODE39_FULL,
	BAR_EX_ITA_PHARMA,
	BAR_EX_CODABAR_ABC,
	BAR_EX_CODABAR_CX,
	BAR_EX_SCODE,
	BAR_EX_MATRIX_2OF5,
	BAR_EX_IATA,
	BAR_EX_KOREAN_POSTAL,
	BAR_EX_CCA,
	BAR_EX_CCB,
	BAR_EX_CCC,
	BAR_EX_LAST
}BARCODES_EX;

/**
 Information about RF card
 */
@interface DTRFCardInfo : NSObject
/**
 RF card type, one of the CARD_* constants
 */
@property (assign) int type;
/**
 RF card type as string, useful for display purposes
 */
@property (copy) NSString *typeStr;
/**
 RF card unique identifier, if any
 */
@property (copy) NSData *UID;
/**
 Mifare card ATQA
 */
@property (assign) int ATQA;
/**
 Mifare card SAK
 */
@property (assign) int SAK;
/**
 ISO15693 card AFI
 */
@property (assign) int AFI;
/**
 ISO15693 card DSFID
 */
@property (assign) int DSFID;
/**
 ISO15693 card block size
 */
@property (assign) int blockSize;
/**
 ISO15693 card number of blocks
 */
@property (assign) int nBlocks;
/**
 FeliCa PMm
 */
@property (copy) NSData *felicaPMm;
/**
 FeliCa Request Data
 */
@property (copy) NSData *felicaRequestData;

/**
 Card index used to access the card from the SDK API
 */
@property (assign) int cardIndex;


@end

/**
 * The class that represents Encrypted Magnetic Head information
 */
@interface EMSRDeviceInfo : NSObject
/**
 * Identification string, for example "EMSR R"
 */
@property (copy) NSString *ident;
/**
 * Unique serial number (16 bytes)
 */
@property (copy) NSData *serialNumber;
/**
 * Unique serial number (16 bytes) in hexadeciamal string for display purposes
 */
@property (copy) NSString *serialNumberString;
/**
 * Firmware version number in format MAJOR*100+MINOR, i.e. ver 1.12 will be returned as 112
 */
@property (assign) int firmwareVersion;
/**
 * Firmware version number in string format, for display purposes
 */
@property (copy) NSString *firmwareVersionString;
/**
 * Security firmware version number in format MAJOR*100 + MINOR, i.e. version 1.12 will be presented as 112
 */
@property (assign) int securityVersion;
/**
 * Firmware version number in string format, for display purposes
 */
@property (copy) NSString *securityVersionString;

@end


/**
 * The class that represents Encrypted Magnetic Head key
 */
@interface EMSRKey : NSObject
/**
 * The ID of the key, one of the KEY_* constants
 */
@property (assign) int keyID;
/**
 * The version of the key
 */
@property (assign) int keyVersion;

/**
 * The name of the key (for display purposes)
 */
@property (copy) NSString *keyName;

@end

/**
 Encryption key, if set magnetic card data will be encrypted
 */
#define KEY_ENCRYPTION 0x01
/**
 Encrypted head key loading key
 */
#define KEY_EH_AES256_LOADING 0x02
/**
 Encrypted head TMK key
 */
#define KEY_EH_TMK_AES 0x10
/**
 Encrypted head DUKPT master key
 */
#define KEY_EH_DUKPT_MASTER 0x20



/**
 * The class that represents Encrypted Magnetic Head keys information
 */
@interface EMSRKeysInfo : NSObject
/**
 * An array of EMSRKey objects representing the keys in the head
 */
@property (copy) NSArray *keys;
/**
 * Indicates if the head is tampered or not. Tampered head needs to be reactivated at secure facility after checking
 */
@property (assign) bool tampered;

/**
 Returns key version or 0 if the key is not loaded
 @param keyID key ID, one of the KEY_* constants
 @return key version or 0 if the key is missing
 */
-(int)getKeyVersion:(int)keyID;

@end

#define UPDATE_INIT ASC_UPDATE_INIT
#define UPDATE_ERASE ASC_UPDATE_ERASE
#define UPDATE_WRITE ASC_UPDATE_WRITE
#define UPDATE_FINISH ASC_UPDATE_FINISH
#define UPDATE_COMPLETING ASC_UPDATE_COMPLETING

/**
 AES128 data encryption key
 */
#define KEY_TYPE_AES128_DATA 0x01
/**
 AES128 key encryption key
 */
#define KEY_TYPE_AES128_KEK 0x81

/**
 AES256 data encryption key
 */
#define KEY_TYPE_AES256_DATA 0x02
/**
 AES256 key encryption key
 */
#define KEY_TYPE_AES256_KEK 0x82

/**
 DES data encryption key
 */
#define KEY_TYPE_DES_DATA 0x03
/**
 DES key encryption key
 */
#define KEY_TYPE_DES_KEK 0x83

/**
 3DES data encryption key
 */
#define KEY_TYPE_3DES_DATA 0x04
/**
 3DES key encryption key
 */
#define KEY_TYPE_3DES_KEK 0x84

/**
 DUKPT/3DES data encryption key
 */
#define KEY_TYPE_DUKPT_3DES_DATA 0x05

/**
 RSA2048 data encryption key
 */
#define KEY_TYPE_RSA2048_DATA 0x06


#endif

/**
 Firmware update phases
 */
typedef enum {
    /**
     Initializing update
     */
	ASC_UPDATE_INIT=0,
    /**
     Erasing old firmware/preparing memory
     */
	ASC_UPDATE_ERASE,
    /**
     Writing data
     */
    ASC_UPDATE_WRITE,
    /**
     Update complete, this is the final phase
     */
    ASC_UPDATE_FINISH,
    /**
     Post-update operations
     */
    ASC_UPDATE_COMPLETING
}ASCFirmwareUpdatePhase;

/**
 * The class that describes the detected card
 */
@interface ASCCardInfo : NSObject

/**
 Detected card type - either magnetic or smart
 */
@property (assign) ASCCardType cardType;
/**
 * Answer To Reset block in case of SmartCard
 */
@property (copy) NSData *atr;
/**
 * Track 1 was read
 */
@property (assign) bool track1Read;
/**
 * Track 2 was read
 */
@property (assign) bool track2Read;
/**
 * Track 3 was read
 */
@property (assign) bool track3Read;
/**
 * RF Card information, available only when RF card was detected
 */
@property (assign) DTRFCardInfo *rfCardInfo;


@end


/**
 * The class that represents financial card parsed information
 */
@interface ASCFinancialCardInfo : NSObject

/**
 * Cardholder name or nil if the field is unavailable
 */
@property (copy) NSString *name;
/**
 * Account number or nil if the field is unavailable
 */
@property (copy) NSString *number;
/**
 * Expiration date month or 0 if the field is unavailable
 */
@property (assign) int expirationMonth;
/**
 * Expiration date year or 0 if the field is unavailable
 */
@property (assign) int expirationYear;
/**
 * Service Code
 *
 */
@property (copy) NSString *serviceCode;


/**
 * Encrypted card data, containing:
 *
 */
@property (copy) NSData *encryptedCardData;

@end

/**
 * The class that represents device information
 */
@interface ASCDeviceInfo : NSObject

/**
 * Identification string, for example "AUDIO SCR"
 */
@property (copy) NSString *ident;
/**
 * Unique serial number
 */
@property (copy) NSString *serialNumber;
/**
 * Firmware version number in format MAJOR*1000+MINOR, i.e. ver 1.950 will be returned as 1950
 */
@property (assign) int firmwareVersion;
/**
 * Firmware version number in string format, for display purposes
 */
@property (copy) NSString *firmwareVersionString;
/**
 * Battery capacity in the range of 0.0-1.0. 0.0 means the battery capacity is unavailable (might happen when battery is charging)
 */
@property (assign) float batteryCapacity;
/**
 * Battery voltage in volts, 0.0 means the battery voltage is unavailable (might happen when battery is charging)
 */
@property (assign) float batteryVoltage;
/**
 * Battery charging state - charging, discharging or just completed charging
 */
@property (assign) ASCChargingState batteryChargingState;

@end



/**
 * The class that represents a device key info
 */
@interface DeviceKey : NSObject
/**
 * The type of the key, one of the KEY_TYPE_* constants
 */
@property (assign) int keyType;
/**
 * The index of the key, 0 represents the first key of that type
 */
@property (assign) int keyIndex;
/**
 * The version of the key or 0 if the key is not set
 */
@property (assign) uint keyVersion;

/**
 * The name of the key (for display purposes)
 */
@property (copy) NSString *keyName;

@end


/**
 * The class that represents Encrypted Magnetic Head keys information
 */
@interface DeviceKeysInfo : NSObject
/**
 * An array of DeviceKey objects representing the keys in the device
 */
@property (copy) NSArray *keys;
/**
 * Indicates if the device is tampered or not. Tampered head needs to be reactivated at secure facility after checking
 */
@property (assign) bool tampered;

/**
 Returns key version or 0 if the key is not loaded
 @param keyType key type, one of the KEY_TYPE_* constants
 @param keyIndex the index of the key, 0 for the first of that type
 @return key version or 0 if the key is missing
 */
-(int)getKeyVersion:(int)keyType keyIndex:(int)keyIndex;

@end


/**
 * The class that represents card status response.
 */
@interface MessageResponse : NSObject

/**
 * The command identifier
 */
@property (assign) int cid;
/**
 * Reserved for future use.
 */
@property (assign) int reserved;
/**
 * Response data.
 */
@property (copy) NSData *data;

-(id)initWithData:(NSData *)data;
@end

/**
 * The class that represents card status response.
 */
@interface EMVChecksumResponse : NSObject

/**
 * Command result
 */
@property (assign) int result;
/**
 * The checksum as returned by EMV.LIB.
 */
@property (copy) NSData *checksum;

@end


enum {
    /**
     Operation in progress
     **/
    ASCStatus_IN_PROGRESS = 90,
    /**
     Operation completed successfully
     **/
    ASCStatus_STATUS_OK = 100,
    /**
     Unknown error occured
     **/
    ASCStatus_STATUS_GENERAL_ERROR = 1,
    /**
     Invalid or unsupported command type was used
     **/
    ASCStatus_STATUS_INVALID_COMMAND_TYPE = 2,
    /**
     Invalid or unsupported command was used
     **/
    ASCStatus_STATUS_INVALID_COMMAND_NUMBER = 3,
    /**
     Invalid command data or wrong arguments
     **/
    ASCStatus_STATUS_INVALID_COMMAND_DATA = 4,
    /**
     The operation requires that card module is enabled
     **/
    ASCStatus_STATUS_CARD_NOT_ENABLED = 5,
    /**
     The operation requires that the card is powered on
     **/
    ASCStatus_STATUS_CARD_NOT_POWERED = 6,
    /**
     No card was found
     **/
    ASCStatus_STATUS_CARD_NOT_PRESENT = 7,
    /**
     Unknown error working with the card
     **/
    ASCStatus_STATUS_CARD_INTERNAL_ERROR = 8,
    /**
     Another command is expected at the time
     **/
    ASCStatus_STATUS_INVALID_COMMAND_SEQUENCE = 9,
    /**
     Supplied data length does not match the required from the command
     **/
    ASCStatus_STATUS_INVALID_LENGTH = 10,
    /**
     Invalid name
     **/
    ASCStatus_STATUS_INVALID_NAME = 11,
    /**
     Invalid command format
     **/
    ASCStatus_STATUS_INVALID_FORMAT = 12,
    /**
     Firmware update: invalid memory address was sent
     **/
    ASCStatus_STATUS_INVALID_ADDRESS = 13,
    /**
     Firmware update: error in cryptography module
     **/
    ASCStatus_STATUS_ENCRYPTION_ERROR = 14,
    /**
     Firmware update: firmware file corrupted or contains invalid signature
     **/
    ASCStatus_STATUS_SIGNATURE_ERROR = 15,
    /**
     Command failed: battery low
     **/
    ASCStatus_STATUS_BATTERY_LOW = 16,
    /**
     Command failed: device is tampered
     **/
    ASCStatus_STATUS_TAMPERED = 17,

    /**
     Command failed: no data available
     **/
    ASCStatus_STATUS_NO_DATA = 21,
    /**
     Command failed: module timeout
     **/
    ASCStatus_STATUS_MODULE_TIMEOUT = 22,
    
    /**
     Timeout communicating with the reader
     **/
    ASCStatus_STATUS_TIMEOUT = -1,
    /**
     Reader not plugged in
     **/
    ASCStatus_NO_DEVICE_PLUGGED_IN = -2,
    /**
     Invalid data was received
     **/
    ASCStatus_STATUS_COMMUNICATION_ERROR = -3,
    /**
     Device is busy (or in firmware update)
     **/
    ASCStatus_STATUS_BUSY = -4,
    /**
     Impossible to write to the audio port
     **/
    ASCStatus_STATUS_AUDIO_ERROR = -5,
};


typedef NSInteger ASCStatus;

/**
 Primary Account Number
 */
extern NSString * const ASCCardComponentKeyAccountNumber;
/**
 Expiration date - month (1-12)
 */
extern NSString * const ASCCardComponentKeyCardExpMonth;
/**
 Expiration date - year
 */
extern NSString * const ASCCardComponentKeyCardExpYear;
/**
 Cardholder's name
 */
extern NSString * const ASCCardComponentKeyCardHolder;

/**
 Magnetic tracks read modes
 */
typedef enum {
    /**
     The track data will never be returned
     */
    ASCTrackReadModeNotAllowed=0,
    /**
     The track data will be returned if it is correctly read or present at all
     */
    ASCTrackReadModeAllowed=1,
    /**
     The read will not be successful unless this track was correctly read
     */
    ASCTrackReadModeRequired=2,
}ASCTrackReadMode;

/**
 Encryption types
 */
typedef enum {
    /**
     Encrypted Magnetic Head AES 256 encryption algorithm
     After decryption, the result data will be as follows:
     - (4 bytes) random data
     - (16 bytes) device identification text, the head unique serial number
     - (variable length) processed track data in the format: 0xF1 (track1 data), 0xF2 (track2 data) 0xF3 (track3 data). It is possible some of the tracks will be empty, then the identifier will not be present too, for example 0xF1 (track1 data) 0xF3 (track3 data)
     - (1 byte) end of track data (byte 0x00)
     - (2 bytes) CRC16CCIT - the CRC is performed from the start of the encrypted block (the Random Data block) to the end of the track data (including the 0x00 byte).
     The data block is padded using PCKS#7
     */
    ASCEncryptionTypeAES256=2,
    /**
     Encrypted Magnetic Head IDTECH encryption algorithm, please refer to IDTECH documentation for detailed format and examples.
     The packet has the following format:
     - (1 byte) encryption type in the upper 5 bits, the tracks read in the lower 3 bits
     - (1 byte) card encoding type, can ignore
     - (1 byte) bits marking which track is present
     - (1 byte) track 1 UNENCRYPTED length
     - (1 byte) track 2 UNENCRYPTED length
     - (1 byte) track 3 UNENCRYPTED length
     - (track 1 UNENCRYPTED length bytes) track 1 masked data
     - (track 2 UNENCRYPTED length bytes) track 2 masked data
     - (track 3 UNENCRYPTED length bytes) track 3 masked data
     - (variable bytes) Track 1 + Track 2 encrypted data, the length of this block is calculated by substracting from the end
     - (20 bytes) track 1 sha1
     - (20 bytes) track 2 sha1
     - (10 bytes) KSN
     
     Encrypted block contents after decryption (3DES):
     - (track 1 UNENCRYPTED length bytes) track 1 data
     - (track 2 UNENCRYPTED length bytes) track 2 data
     */
    ASCEncryptionTypeIDTECH=3,
    /**
     Card data will be sent encrypted in the format:
     - (1 byte) encryption type in the upper 5 bits, the tracks read in the lower 3 bits
     - (256 bytes) RSA key block in PKCS1 format
     - (13 bytes, string)device unique serial number
     - (3 bytes) padding, zeroes
     - (4 bytes) random data
     - (variable length) track 2 data, 00 terminated
     - (variable length) cardholder name, 00 terminated
     - (32 bytes) sha256 on all the data starting with the serial number, padding, random data, track 2 data and cardholder name
     - (variable length) padding data - bytes with value 00
     Random data, track 2 data, cardholder name, sha256 and the padding are encrypted with AES128
     **/
    ASCEncryptionTypeRSAOld=0,
    ASCEncryptionTypeRSA=5,
} ASCEncryptionType;


/**
 Provides access to AudioReader accessory functionality.
 */
@interface AudioSmartCardReader : NSObject <NSStreamDelegate>
{
@private
    NSData *savedATR;
}


/** @defgroup G_AUDGENERAL General functions
 @ingroup G_AUDIOREADER
 Functions to initialize and connect/disconnect to the reader
 @{
 */

/**
 Creates and initializes new class instance or returns already initalized one. Use this function, if you want to access the class from different places
 @return shared class instance
 **/
+(id)sharedDevice;

/**
 Checks if audio reader is plugged in. This function goes not guarantee 100% correct result, as it will return true when headset with microphone is plugged
 @return TRUE if audio reader is present, false otherwise
 */
-(BOOL)isPluggedIn;

/**
 Tries to connect to the AudioReader device via the microphone port. Call this function before any other.
 @note In order to save battery do not leave the reader powered on for extended periods of time.
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(bool)powerOn:(NSError **)error;

/**
 Powers down the connected reader and stops microphone port to save battery.
 **/
-(void)powerOff;

/**
 Special usage case function only, do not use unless you have another software that modifies audio settings at wrong time.
 **/
-(void)forceReinit;

/**
 Returns information about the connected device
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return device information class or nil if error occured
 **/
-(ASCDeviceInfo *)getDeviceInfo:(NSError **)error;

/**
 Returns information about the specified firmware data. Based on it, and the connected device's name, model and firmware version you can chose to update or not device's firmware
 @param data - firmware data
 <table>
 <tr><td>"deviceName"</td><td>Device name</td></tr>
 <tr><td>"deviceModel"</td><td>Device model</td></tr>
 <tr><td>"firmwareRevision"</td><td>Firmware revision as string, for example 1.950</td></tr>
 <tr><td>"firmwareRevisionNumber"</td><td>Firmware revision as number MAJOR*1000+MINOR, i.e. 1.950 will be returned as 1950</td></tr>
 </table>
 @return firmware information if function succeeded, nil otherwise
 **/
-(NSDictionary *)getFirmwareFileInformation:(NSData *)data;

//-------------------------------------------------------------------------------------


/**@}*/


/** @defgroup G_AUDCARD SmartCard/Magnetic Card functions
 @ingroup G_AUDIOREADER
 Functions to work with the SmartCards and Magnetic Cards
 @{
 */

/**
 Extracts magnetic card data from the smartcard and return the data block. This command can be called directly after powerOn, it does all nessecary operations to enable the reader module, power on the smartcard, find and extract the data, then power off the smartcard.
 @param encryption the type of encryption to use for the data, one of the ENCRYPTION_* constants
 @param timeout the time it tries to read the card, this parameter only works with magnetic cards, smartcard reader directly return
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return encrypted financial card data if function succeeded, nil otherwise
 **/
-(NSData *)getFinancialCardDataUsingEncryption:(ASCEncryptionType)encryption timeout:(NSTimeInterval)timeout error:(NSError **)error;

/**
 Changes the settings for magnetic card reading using waitForCard function. Call this function before using waitForCard.
 @param encryption the type of encryption to use for the magnetic card data
 @param track1Mode controls if the track will be read if present, discarded or required
 @param track2Mode controls if the track will be read if present, discarded or required
 @param track3Mode controls if the track will be read if present, discarded or required
 **/
-(void)setMagneticCardModeEncryption:(ASCEncryptionType)encryption track1Mode:(ASCTrackReadMode)track1Mode track2Mode:(ASCTrackReadMode)track2Mode track3Mode:(ASCTrackReadMode)track3Mode;

/**
 Fine-tunes which part of the card data will be masked, and which will be sent in clear text for display/print purposes
 @param showExpiration if set to TRUE, expiration date will be shown in clear text, otherwise will be masked
 @param unmaskedDigitsAtStart the number of digits to show in clear text at the start of the PAN, range from 0 to 6 (default is 4)
 @param unmaskedDigitsAtEnd the number of digits to show in clear text at the end of the PAN, range from 0, to 4 (default is 4)
 */
-(void)setMagneticCardMaskModeShowExpiration:(BOOL)showExpiration unmaskedDigitsAtStart:(int)unmaskedDigitsAtStart unmaskedDigitsAtEnd:(int)unmaskedDigitsAtEnd;

/**
 Fine-tunes which part of the card data will be masked, and which will be sent in clear text for display/print purposes
 @param showExpiration if set to TRUE, expiration date will be shown in clear text, otherwise will be masked
 @param showServiceCode if set to TRUE, service code will be shown in clear text, otherwise will be masked
 @param unmaskedDigitsAtStart the number of digits to show in clear text at the start of the PAN, range from 0 to 6 (default is 4)
 @param unmaskedDigitsAtEnd the number of digits to show in clear text at the end of the PAN, range from 0, to 4 (default is 4)
 */
-(void)setMagneticCardMaskModeShowExpiration:(BOOL)showExpiration showServiceCode:(BOOL)showServiceCode unmaskedDigitsAtStart:(int)unmaskedDigitsAtStart unmaskedDigitsAtEnd:(int)unmaskedDigitsAtEnd;

/**
 Waits for card. Depending on the hardware type, it can either be magnetic, smart or nfc card. The function returns when a card is found and gives basic card info.
 @param timeout the time it tries to read the card
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return card information if function succeeded, nil otherwise
 **/
-(ASCCardInfo *)waitForCard:(NSTimeInterval)timeout error:(NSError **)error;

/**
 Cancels waitForCard operation. You need to call this function on another thread than current waitForCard call
 **/
-(void)waitForCardCancel;

/**
 After magnetic card was swiped, use this function to get the encrypted data block, according to the encryption mode selected with msSetSettingsEncryption
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return encrypted financial card data if function succeeded, nil otherwise
 **/
-(NSData *)msGetEncryptedCardData:(NSError **)error;

/**
 Queries the reader for masked card data. This function needs to be called immediatelly after reading, or the information will be deleted
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return financial card data if function succeeded, nil otherwise
 **/
-(ASCFinancialCardInfo *)msGetFinancialCardMaskedData:(NSError **)error;

/**
 Helper function to parse financial card and extract the data - name, number, expiration date. The function will extract as much information as possible.
 @param track1 - track1 information or nil
 @param track2 - track2 information or nil
 @return dictionary containing extracted data or nil if the data is invalid. Keys contained are:
 <table>
 <tr><td>"accountNumber"</td><td>Account number</td></tr>
 <tr><td>"cardholderName"</td><td>Cardholder name, as stored in the card</td></tr>
 <tr><td>"expirationYear"</td><td>Expiration date - year</td></tr>
 <tr><td>"expirationMonth"</td><td>Expiration date - month</td></tr>
 <tr><td>"serviceCode"</td><td>Service code (if any)</td></tr>
 <tr><td>"discretionaryData"</td><td>Discretionary data (if any)</td></tr>
 <tr><td>"firstName"</td><td>Extracted cardholder's first name</td></tr>
 <tr><td>"lastName"</td><td>Extracted cardholder's last name</td></tr>
 </table>
 **/
-(NSDictionary *)msProcessFinancialCard:(NSString *)track1 track2:(NSString *)track2;

/**@}*/



/** @defgroup G_EMV EMV Reader Functions
 @ingroup G_AUDIOREADER
 Functions available on the EMV reader
 @{
 */


/**@}*/



/** @defgroup G_DUKPT DUKPT Reader Functions
 @ingroup G_AUDIOREADER
 Functions available on the DUKPT reader
 @{
 */

/**
 Transmits encrypted APDU command to smart card (<i>Supported by DUKPT reader</i>).
 
 <p>
 The encrypted data format is:
 <table border="1">
 <tr>
 <td>Data length (2 bytes, only the length of the real APDU data)</td>
 <td>Data (APDU data bytes)</td>
 <td>CRC16 (2 bytes, calculated on all bytes before the CRC)</td>
 <td>Padding (0 - 7 bytes depending packet size)</td>
 </tr>
 </table>
 
 @param data encrypted APDU block
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return encrypted APDU response if function succeeded, nil otherwise
 */
-(NSData *)scEncryptedCAPDU:(NSData *)data error:(NSError **)error;

/**
 * Get IPEK version (<i>Supported by DUKPT reader</i>).
 *
 * @param version upon success stores IPEK version (0 means the key is not set)
 * @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 * @return TRUE if function succeeded, FALSE otherwise
 */
-(bool)kmGetIPEKVersion:(int *)version error:(NSError **)error;

/**
 * Get KEK version (<i>Supported by DUKPT reader</i>).
 *
 * @param version upon success stores KEK version (0 means the key is not set)
 * @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 * @return TRUE if function succeeded, FALSE otherwise
 */
-(bool)kmGetKEKVersion:(int *)version error:(NSError **)error;

/**
 * Generate new DUKPT key and return KSN (<i>Supported by DUKPT reader</i>).
 *
 * @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 * @return KSN (10 bytes) if function succeeded, nil otherwise
 */
-(NSData *)kmGetKSN:(NSError **)error;

/**
 * Load DUKPT 3DES IPEK (<i>Supported by DUKPT reader</i>).
 *
 * <p>
 * If IPEK version is equal to 0 then key block must be provided in plain text. Otherwise, it
 * must be encrypted with KEK.
 *
 * <p>
 * The key block format is:
 * <table border="1">
 * <tr>
 * <td>IPEK version (4 bytes)</td>
 * <td>IPEK (16 bytes)</td>
 * <td>KSN (10 bytes)</td>
 * <td>SHA256 (32 bytes or missing when send in plain text)</td>
 * <td>Padding (2 bytes or missing when send in plain text)</td>
 * </tr>
 * </table>
 * <i>Note: 'SHA256' field contains the checksum of all previous fields starting from 'IPEK version'. The 'IPEK version' is expected to be in big endian format (MSB first).</i>
 *
 * @param ipek the key data.
 *
 * @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 * @return TRUE if function succeeded, FALSE otherwise
 */
-(bool)kmLoadIPEK:(NSData *)ipek error:(NSError **)error;

/**
 * Load 3DES KEK (<i>Supported by DUKPT reader</i>).
 *
 * <p>
 * If KEK version is equal to 0 then key block must be provided in plain text. Otherwise, it
 * must be encrypted with KEK.
 *
 * <p>
 * The key block format is:
 * <table border="1">
 * <tr>
 * <td>KEK version (4 bytes)</td>
 * <td>KEK (16 bytes)</td>
 * <td>SHA256 (32 bytes or missing when send in plain text)</td>
 * <td>Padding (4 bytes or missing when send in plain text)</td>
 * </tr>
 * </table>
 * <i>Note: 'SHA256' field contains the checksum of all previous fields starting from 'KEK version'. The 'KEK version' is expected to be in big endian format (MSB first).</i>
 *
 * @param kek the key block data.
 *
 * @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 * @return TRUE if function succeeded, FALSE otherwise
 */
-(bool)kmLoadKEK:(NSData *)kek error:(NSError **)error;

/**
 * Set the initial vector for data encryption (<i>Supported by DUKPT reader</i>).
 *
 * @param iv Initialization Vector
 * @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 * @return TRUE if function succeeded, FALSE otherwise
 */
-(bool)kmSetInitialVector:(NSData *)iv error:(NSError **)error;

/**
 * Load/Change RSA key  (<i>Supported by EMV reader</i>).
 * The new RSA public key is signed by old RSA's private key to allow loading. If you have PUB1, PRIV1 and PUB2, PRIV2
 *
 * <p>
 * The key block format is:
 * <table border="1">
 * <tr>
 * <td>RSA Signature (256 bytes): PCKS#1 SHA256 of the new RSA public key, encrypted(signed) with old RSA's private key</td>
 * <td>RSA Key version (4 bytes): The RSA key version in big endian</td>
 * <td>RSA Key (256 bytes): The RSA2048 key data</td>
 * </tr>
 * </table>
 *
 * @param keyBlock the RSA key block according to the format specified above
 * @param index RSA key index, pass 0 for now
 * @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 * @return TRUE if function succeeded, FALSE otherwise
 */
-(bool)kmLoadRSAKey:(NSData *)keyBlock index:(int)index error:(NSError **)error;

/**
 * Forces generation of a new symmetric key used by RSA (<i>Supported by EMV reader</i>).
 * @param symmetricKeyType symmetric key type, either KEY_TYPE_AES128_DATA or KEY_TYPE_AES256_DATA
 * @param rsaKeyIndex RSA key index, pass 0 for now
 * @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 * @return TRUE if function succeeded, FALSE otherwise
 */
-(bool)kmGenerateRSASymmetricKeyType:(int)symmetricKeyType rsaKeyIndex:(int)rsaKeyIndex error:(NSError **)error;

/**
 * Retrieves information about loaded keys in the reader (<i>Supported by EMV reader</i>).
 * @note The encrypted magnetic head part (EMSR) features its own keys, it is emsr* functions dealing with them
 * @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 * @return DeviceKeysInfo if function succeeded, nil otherwise
 */
-(DeviceKeysInfo *)kmGetKeysInfo:(NSError **)error;

/**
 Returns general information about the encrypted head - firmware version, ident, serial number
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return EMSRDeviceInfo object if function succeeded, nil otherwise
 **/
-(EMSRDeviceInfo *)emsrGetDeviceInfo:(NSError **)error;

/**
 Returns information about the loaded keys in the encrypted head and tampered status
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return EMSRKeysInfo object if function succeeded, nil otherwise
 **/
-(EMSRKeysInfo *)emsrGetKeysInfo:(NSError **)error;

/**
 Returns information about the specified head firmware data. Based on it, and the current head's name and firmware version you can chose to update or not the head's firmware
 @param data - firmware data
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return dictionary containing extracted data or nil if the data is invalid. Keys contained are:
 <table>
 <tr><td>"deviceModel"</td><td>Head's model, for example "EMSR-DEA"</td></tr>
 <tr><td>"firmwareRevision"</td><td>Firmware revision as string, for example 1.07</td></tr>
 <tr><td>"firmwareRevisionNumber"</td><td>Firmware revision as number MAJOR*100+MINOR, i.e. 1.07 will be returned as 107</td></tr>
 </table>
 **/
-(NSDictionary *)emsrGetFirmwareInformation:(NSData *)data error:(NSError **)error;

/**
 Loads new key, in plain or encrypted with already loaded AES256 Key Encryption Key (KEK). Plain text loading works only the first time the specified key is loaded and is recommended only in secure environment. For normal usage the new key should be encrypted with the Key Encryption Key (KEK). The command is unavailable if the device is tampred.
 @param keyData an array, that consists of:
 - MAGIC NUMBER - (1 byte) 0x2b
 - ENCRYPTION KEY ID - (1 byte) the ID of the already existing key, used to encrypt the new key data. Set it to KEY_EH_AES256_LOADING (0x02) if you want to set the key in encrypted state or 0xFF for plain state.
 - KEY ID - (1 byte) the ID of the key to set, one of the KEY_ constants. The TMK cannot be changed with this command.
 - KEY VERSION - (4 bytes) the version of the key in high to low order, 4 bytes, cannot be 0
 - KEY - (variable) the key data, length depends on the key in question, AES256 keys are 32 bytes, DUKPT key is 16 bytes key, 10 bytes serial, 6 bytes for padding (zeroes)
 - HASH - SHA256 of the previous bytes (MAGIC NUMBER, ENCRYPTION KEY ID, KEY ID, KEY VERSION, KEY)
 
 <br>If using KEY_EH_AES256_LOADING, then KEY + HASH have to be put inside the packet encrypted with AES256 using key KEY_EH_AES256_LOADING. SHA256 is calculated on the unencrypted data. The head decrypts the data and then calculates and compares the hash. If the calculated SHA does not match the SHA sent with the command, the key excahnge is rejected and error is returned.
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)emsrLoadKey:(NSData *)keyData error:(NSError **)error;

/**
 Updates device firmware with specified firmware data. The firmware can only be upgraded or downgraded, if you send the same firmware version, then no update process will be started.
 @note The update process is quite sturdy, even if interrupted, the device will still be useable and can be updated again.
 @param data the firmware data
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(bool)updateFirmware:(NSData *)data error:(NSError **)error;

-(bool)barStartScan:(NSError **)error;
-(bool)barStopScan:(NSError **)error;
-(NSString *)barcodeType2Text:(int)barcodeType;

-(NSData *)rfProcessPaymentCard:(int)channel error:(NSError **)error;

/**@}*/

/**
 Current state of the reader hardware
 */
@property(readonly) bool isPoweredOn;

/**
 Adds delegate to the class
 **/
@property(unsafe_unretained) id delegate;

/**
 SDK version number in format MAJOR*1000+MINOR, i.e. ver 1.950 will be returned as 1950
 */
@property(readonly) int sdkVersion;

/**
 @deprecated
 Compatibility only, do not use
 */
@property(assign) int batteryVoltage DEPRECATED_ATTRIBUTE;

@end

/**
 Protocol describing various notifications that AudioReaderSDK can send.
 @ingroup G_AUDIOREADER
 */
@protocol AudioReaderDelegate
@optional
/** @defgroup G_ARDELEGATE Delegate Notifications
 @ingroup G_AUDIOREADER
 Notifications sent by the sdk on various events - currently on firmware update
 @{
 */

/**
 Notification sent, when the audio reader (or headphones+microphone) is plugged in
 */
- (void)readerDidUnplug:(AudioSmartCardReader*)audioReader;

/**
 Notification sent, when the plugged audio reader was unplugged
 */
- (void)readerDidPlugIn:(AudioSmartCardReader*)audioReader;

/**
 Notification sent when firmware update process advances. Do not call any other functions until firmware update is complete! During the firmware update notifications will be posted.
 @param phase one of the ASCFirmwareUpdatePhase constants
 @param percent firmware update progress in percents
 **/
-(void)firmwareUpdateProgress:(ASCFirmwareUpdatePhase)phase percent:(int)percent;

/**
 Notification sent when barcode is successfuly read. This notification is used when barcode type is set to BARCODE_TYPE_DEFAULT or BARCODE_TYPE_EXTENDED.
 @param barcode - string containing barcode data
 @param type - barcode type, one of the BAR_* constants
 **/
-(void)barcodeData:(NSString *)barcode type:(int)type;
/**@}*/

@end

#pragma mark DEPRECATED

@interface AudioSmartCardReader (Deprecated)

/** @defgroup G_DEP_AUDIO Deprecated Audio Functions
 @ingroup G_AUDIOREADER
 Deprecated functions, please check out synchronous alternatives
 @{
 */

/**
 Tries to connect to the AudioReader device via the microphone port. Call this function before any other.
 @note In order to save battery do not leave the reader powered on for extended periods of time.
 @param block the function block that will be called upon function completion
 - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 **/
-(void)powerOnWithCompletionBlock:(void (^)(ASCStatus status))block;

/**
 Powers down the connected reader and stops microphone port to save battery.
 @param block the function block that will be called upon function completion
 - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 **/
-(void)powerOffWithCompletionBlock:(void (^)(ASCStatus status))block;

/**
 Returns connected reader name and firmware version
 @param block the function block that will be called upon function completion
 - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 - ident returns device identification string
 - ersion returns firmware version in format MAJOR*1000+MINOR, i.e. ver 1.950 will be returned as 1950
 **/
-(void)getIdentifierAndVersionWithCompletionBlock:(void (^)(ASCStatus status, NSString *ident, int version))block;

/**
 Returns connected reader's serial number
 @param block the function block that will be called upon function completion
 - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 - sn returns device unique serial number
 **/
-(void)getSerialNumberWithCompletionBlock:(void (^)(ASCStatus status, NSString *sn))block;

/**
 Returns information about the battery
 @param block the function block that will be called upon function completion
 - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 - capacity battery capacity in the range of 0.0-1.0. 0.0 means the battery capacity is unavailable (might happen when battery is charging)
 - chargingState battery charging state - charging, discharging or just completed charging
 */
-(void)getBatteryInfoWithCompletionBlock:(void (^)(ASCStatus status, float capacity, ASCChargingState chargingState))block;

/**
 Updates device firmware with specified firmware data. The firmware can only be upgraded or downgraded, if you send the same firmware version, then no update process will be started.
 @note The update process is quite sturdy, even if interrupted, the device will still be useable and can be updated again.
 @param data the firmware data
 @param block the function block that will be called upon function completion
 - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 - phase firmware update phase, one of the UPDATE_* constants
 - progress firmware update progress, ranges from 0.0 to 1.0
 - stop if set to true, firmware update will be cancelled
 */
-(void)updateFirmware:(NSData *)data completionBlock:(void (^)(ASCStatus status, ASCFirmwareUpdatePhase phase, float progress, BOOL *stop))block;

/**
 Updates device firmware with specified firmware data. The firmware can only be upgraded or downgraded, if you send the same firmware version, then no update process will be started.
 @note The update process is quite sturdy, even if interrupted, the device will still be useable and can be updated again.
 @param data the firmware data
 @param statusUpdate optional function that will be called to update the display
 - phase firmware update phase, one of the UPDATE_* constants
 - progress firmware update progress, ranges from 0.0 to 1.0
 - stop if set to true, firmware update will be cancelled
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return true if function succeeded, false otherwise
 */
-(BOOL)updateFirmware:(NSData *)data statusUpdate:(void (^)(ASCFirmwareUpdatePhase phase, float progress, BOOL *stop))statusUpdate error:(NSError **)error;

/**
 Extracts magnetic card data from the smartcard and return the data block. This command can be called directly after powerOn, it does all nessecary operations to enable the reader module, power on the smartcard, find and extract the data, then power off the smartcard.
 @param encryption the type of encryption to use for the data, one of the ENCRYPTION_* constants
 @param block the function block that will be called upon function completion
 - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 - data encrypted card data
 - info additional masked information, like cardholder name, masked number, expiration date
 **/
-(void)getFinancialCardDataUsingEncryption:(ASCEncryptionType)encryption completionBlock:(void (^)(ASCStatus status, ASCEncryptionType encryption, NSData *data, NSDictionary *info))block;

/**
 Extracts magnetic card data from magnetic or smartcard and return the data block. This command can be called directly after powerOn, it does all nessecary operations to enable the reader module, power on the smartcard, find and extract the data, then power off the smartcard.
 @param encryption the type of encryption to use for the data, one of the ENCRYPTION_* constants
 @param timeout timeout in seconds, which to wait for the card to be inserted(smartcard) or swiped(magnetic)
 @param block the function block that will be called upon function completion
 - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 - data encrypted card data
 - info additional masked information, like cardholder name, masked number, expiration date
 **/
-(void)getFinancialCardDataUsingEncryption:(ASCEncryptionType)encryption timeout:(NSTimeInterval)timeout completionBlock:(void (^)(ASCStatus status, ASCEncryptionType encryption, NSData *data, NSDictionary *info))block;

/**
 * Transmits the encrypted message stored into data buffer and receives the response. (<i>Supported by EMV reader</i>)
 * <p>
 * Definition for an encrypted message:
 * <table border="1">
 * <tr>
 * <td>1 byte</td>
 * <td>1 byte</td>
 * <td>2 byte</td>
 * <td>(Data length) byte</td>
 * <td>2 byte</td>
 * <td>0-15 byte</td>
 * </tr>
 * <tr>
 * <td>CID</td>
 * <td>RFU</td>
 * <td>Data length</td>
 * <td>Data</td>
 * <td>CRC-CCIT16</td>
 * <td>Padding</td>
 * </tr>
 * </table>
 *
 * @param data the encrypted message data.
 * @param block the function block that will be called upon function completion
 * - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 * - resultData response message data
 */
-(void)transmitEncryptedMessage:(NSData *)data completionBlock:(void (^)(ASCStatus status, NSData *resultData))block;

/**
 * Transmits the plain text message stored into data buffer and receives the response. (<i>Supported by EMV reader</i>)
 * <p>
 * Definition for a message:
 * <table border="1">
 * <tr>
 * <td nowrap="nowrap">1 byte</td>
 * <td nowrap="nowrap">1 byte</td>
 * <td nowrap="nowrap">2 byte</td>
 * <td nowrap="nowrap">(Data length) byte</td>
 * <td nowrap="nowrap">2 byte</td>
 * <td nowrap="nowrap">0-15 byte</td>
 * </tr>
 * <tr>
 * <td>CID</td>
 * <td>RFU</td>
 * <td>Data length</td>
 * <td>Data</td>
 * <td>CRC-CCIT16</td>
 * <td>Padding</td>
 * </tr>
 * </table>
 *
 * @param data the message data.
 * @param block the function block that will be called upon function completion
 * - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 * - result response message data
 */
-(void)transmitMessage:(NSData *)data completionBlock:(void (^)(ASCStatus status, MessageResponse *result))block;

/**
 * Transmit message. (<i>Supported by EMV reader</i>)
 *
 * @param cid the command identifier.
 * @param data the command data.
 * @param block the function block that will be called upon function completion
 * - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 * - resultData response message data
 */
-(void)transmitMessageCID:(int)cid data:(NSData *)data completionBlock:(void (^)(ASCStatus status, MessageResponse *result))block;

/**
 * Transmit message. (<i>Supported by EMV reader</i>)
 *
 * @param cid the command identifier.
 * @param block the function block that will be called upon function completion
 * - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 * - resultData response message data
 */
-(void)transmitMessageCID:(int)cid completionBlock:(void (^)(ASCStatus status, MessageResponse *result))block;

/**
 * Process message data. (<i>Supported by EMV reader</i>)
 * <p>
 * The message data is prefixed with a fixed length two byte header. This header format is
 * common for encrypted and plain text messages and is a combination of 16 bits.
 * <p>
 * The complete message looks like this:
 * <table border="1">
 * <tr>
 * <td nowrap="nowrap">Header (2 byte)</td>
 * <td nowrap="nowrap">Payload (encrypted or plain text, variable length)</td>
 * </tr>
 * </table>
 * <p>
 * The message header that is always in plain text is defined like this:
 * <table border="1">
 * <tr>
 * <td nowrap="nowrap">Bit(s)</td>
 * <td>Length</td>
 * <td>Description</td>
 * </tr>
 * <tr>
 * <td>1</td>
 * <td>1</td>
 * <td>Indicator for encrypted (ë1í) or plain text (ë0í) format</td>
 * </tr>
 * <tr>
 * <td>2</td>
 * <td>1</td>
 * <td>RFU</td>
 * </tr>
 * <tr>
 * <td>3-16</td>
 * <td>14</td>
 * <td>Payload length in network byte order (Big-Endian). For encrypted data the complete
 * encrypted data length including necessary padding bytes is contained.</td>
 * </tr>
 * </table>
 *
 * @param data the data block, which must contains data packed into message framing format.
 * @param block the function block that will be called upon function completion
 * - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 * - resultData response message data into the same format as input data.
 */
-(void)processMessage:(NSData *)data completionBlock:(void (^)(ASCStatus status, NSData *resultData))block;

/**
 * Get the current configuration version and the response buffer size. (<i>Supported by EMV reader</i>)
 *
 * @param block the function block that will be called upon function completion
 * - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 * - resultData response data
 */
-(void)getConfigurationParameters:(void (^)(ASCStatus status, NSData *resultData))block;

/**
 * Get information if there is a card in the reader or not and additional the actual card power state. (<i>Supported by EMV reader</i>)
 *
 * @param block the function block that will be called upon function completion
 * - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 * - response card status, refer to class description for various card statuses
 */
-(void)getCardStatus:(void (^)(ASCStatus status, CardStatusResponse *response))block;

/**
 * Perform card EMV reset. (<i>Supported by EMV reader</i>)
 *
 * @param block the function block that will be called upon function completion
 * - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 * - response card status, refer to class description for various card statuses
 */
-(void)performCardEMVReset:(void (^)(ASCStatus status, CardResetResponse *response))block;

/**
 * Perform card reset. (<i>Supported by EMV reader</i>)
 *
 * @param block the function block that will be called upon function completion
 * - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 * - response card status, refer to class description for various card statuses
 */
-(void)performCardReset:(void (^)(ASCStatus status, CardResetResponse *response))block;

/**
 * Perform card power off. (<i>Supported by EMV reader</i>)
 *
 * @param block the function block that will be called upon function completion
 * - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 * - response card status, refer to class description for various card statuses
 */
-(void)performCardPowerOff:(void (^)(ASCStatus status, CardStatusResponse *response))block;

/**
 * Wait for card and EMV reset. (<i>Supported by EMV reader</i>)
 *
 * @param timeout the time to wait for a card before returning (in seconds).
 * @param block the function block that will be called upon function completion
 * - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 * - response card status, refer to class description for various card statuses
 */
-(void)waitForCardAndEMVResetTimeout:(float)timeout completionBlock:(void (^)(ASCStatus status, CardResetResponse *response))block;

/**
 * Retrieve the EMV L2 Kernel checksum for any supported configuration. (<i>Supported by DUKPT reader</i>)
 *
 * @param name the name of kernel configuration.
 * @param block the function block that will be called upon function completion
 * - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 * - response emv status response, refer to class description
 */
-(void)getEMVChecksum:(NSString *)name completionBlock:(void (^)(ASCStatus status, EMVChecksumResponse *response))block;

/**
 * Used for security initialization. (<i>Supported by EMV reader</i>)
 * A new session key is generated, encrypted and provided for further use with the protected interface.
 *
 * @param block the function block that will be called upon function completion
 * - status function status, that will be passed to the completion block, ASCStatus_STATUS_OK or one of the ASCStatus_* codes
 * - sessionKeyData the session key data
 */
-(void)enterProtectedMode:(void (^)(ASCStatus status, NSData *sessionKeyData))block;

/**@}*/
@end

/**@}*/


/**
 Helper function to return string from status codes.
 */
NSString *NSStringFromASCStatus(ASCStatus status);


/**@}*/

