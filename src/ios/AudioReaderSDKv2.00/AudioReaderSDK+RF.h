#import "AudioReaderSDK.h"

@class UIImage;

/**
 ISO14443 Type A (Mifare) cards will be detected
 */
#define CARD_SUPPORT_TYPE_A 0x0001
/**
 ISO14443 Type B cards will be detected. Currently unsupported.
 */
#define CARD_SUPPORT_TYPE_B 0x0002
/**
 Felica cards will be detected.
 */
#define CARD_SUPPORT_FELICA 0x0004
/**
 NFC cards will be detected. Currently unsupported.
 */
#define CARD_SUPPORT_NFC 0x0008
/**
 Jewel cards will be detected. Currently unsupported.
 */
#define CARD_SUPPORT_JEWEL 0x0010
/**
 ISO15693 cards will be detected
 */
#define CARD_SUPPORT_ISO15 0x0020
/**
 ST SRI cards will be detected
 */
#define CARD_SUPPORT_STSRI 0x0040

#ifndef RF_STRUCTURES_DEFINED
#define RF_STRUCTURES_DEFINED
/**
 RF card types
 */
typedef enum
{
    /**
     Unknown card
     */
	CARD_UNKNOWN=0,
    /**
     Mifare Mini
     */
	CARD_MIFARE_MINI,
    /**
     Mifare Classic 1K
     */
	CARD_MIFARE_CLASSIC_1K,
    /**
     Mifare Classic 4K
     */
	CARD_MIFARE_CLASSIC_4K,
    /**
     Mifare Ultralight
     */
	CARD_MIFARE_ULTRALIGHT,
    /**
     Mifare Ultralight C
     */
	CARD_MIFARE_ULTRALIGHT_C,
    /**
     ISO 14443A
     */
	CARD_ISO14443A,
    /**
     Mifare Plus
     */
	CARD_MIFARE_PLUS,
    /**
     ISO 15693
     */
	CARD_ISO15693,
    /**
     Mifare Desfire
     */
	CARD_MIFARE_DESFIRE,
    /**
     ISO 14443B
     */
	CARD_ISO14443B,
    /**
     FeliCa
     */
	CARD_FELICA,
    /**
     ST SRI
     */
	CARD_ST_SRI,
    /**
     NFC Payment
     */
	CARD_PAYMENT,
}RF_CARD_TYPES;

/**
 FeliCa SmartTag battery status
 */
typedef enum
{
    /**
     Normal, card can be used
     */
	FELICA_SMARTTAG_BATTERY_NORMAL1=0,
    /**
     Normal, card can be used
     */
	FELICA_SMARTTAG_BATTERY_NORMAL2,
    /**
     Low, consider replacing
     */
    FELICA_SMARTTAG_BATTERY_LOW1,
    /**
     Very Low, replace it
     */
    FELICA_SMARTTAG_BATTERY_LOW2,
}FELICA_SMARTTAG_BATERY_STATUSES;

/**
 FeliCa SmartTag draw mode
 */
typedef enum
{
    /**
     The area outside of the image will be emptied
     */
	FELICA_SMARTTAG_DRAW_WHITE_BACKGROUND=0,
    /**
     The area outside of the image will be shown black
     */
	FELICA_SMARTTAG_DRAW_BLACK_BACKGROUND,
    /**
     The area outside of the image will be kept to its current state
     */
    FELICA_SMARTTAG_DRAW_KEEP_BACKGROUND,
    /**
     The area outside of the image will be drawn using one of the previously stored layouts
     */
    FELICA_SMARTTAG_DRAW_USE_LAYOUT
}FELICA_SMARTTAG_DRAW_MODES;

#endif

@protocol AudioReaderRFDelegate <NSObject>

@end

@interface AudioSmartCardReader (RF)
/**
 * Set the RFID card parameters.
 *
 * @param supportedCards Any combination of CARD_SUPPORT_* flags to mark which card types to be active. Enable only cards you actually plan to work with.
 * This has high implication on power usage and detection speed.
 */
-(void)setRFSupportedCards:(int)supportedCards;

/**
 Authenticate mifare card block with direct key data. This is less secure method, as it requires the key to be present in the program, the prefered way is to store a key once in a secure environment and then authenticate using the stored key.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param type key type, either 'A' or 'B'
 @param address the address of the block to authenticate
 @param key 6 bytes key
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)mfAuthByKey:(int)cardIndex type:(char)type address:(int)address key:(NSData *)key error:(NSError **)error;
/**
 Store key in the internal module memory for later use
 @param keyIndex the index of the key, you can have up to 8 keys stored (0-7)
 @param type key type, either 'A' or 'B'
 @param key 6 bytes key
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)mfStoreKeyIndex:(int)keyIndex type:(char)type key:(NSData *)key error:(NSError **)error;
/**
 Authenticate mifare card block with previously stored key. This the prefered method, as no key needs to reside in application.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param type key type, either 'A' or 'B'
 @param address the address of the block to authenticate
 @param keyIndex the index of the stored key, you can have up to 8 keys stored (0-7)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)mfAuthByStoredKey:(int)cardIndex type:(char)type address:(int)address keyIndex:(int)keyIndex error:(NSError **)error;
/**
 Reads one more more blocks of data from Mifare Classic/Ultralight cards. A single read operation gets 16 bytes of data, so you can pass 32 on length to read 2 blocks, etc
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param address the address of the block to read
 @param length the number of bytes to read, this must be multiple of block size (16 bytes)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return NSData object containing the data received or nil if an error occured
 */
-(NSData *)mfRead:(int)cardIndex address:(int)address length:(int)length error:(NSError **)error;
/**
 Writes one more more blocks of data to Mifare Classic/Ultralight cards. A single write operation stores 16 bytes of data, so you can pass 32 on length to write 2 blocks, etc
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param address the address of the block to write
 @param data the data to write, must be multiple of the block size (16 bytes)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return number of bytes actually written or 0 if an error occured
 */
-(int)mfWrite:(int)cardIndex address:(int)address data:(NSData *)data error:(NSError **)error;
/**
 Sets the 3DES key of Mifare Ultralight C cards
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param key 16 bytes 3DES key to set
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)mfUlcSetKey:(int)cardIndex key:(NSData *)key error:(NSError **)error;
/**
 Performs 3DES authentication of Mifare Ultralight C card using the given key
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param key 16 bytes 3DES key to authenticate with
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)mfUlcAuthByKey:(int)cardIndex key:(NSData *)key error:(NSError **)error;

/**
 Reads one more more blocks of data from ISO 15693 card.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param startBlock the starting block to read from
 @param length the number of bytes to read, this must be multiple of block size (can be taken from the card info that is coming with rfCardDetected call)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return NSData object containing the data received or nil if an error occured
 */
-(NSData *)iso15693Read:(int)cardIndex startBlock:(int)startBlock length:(int)length error:(NSError **)error;
/**
 Writes one more more blocks of data to ISO 15693 card.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param startBlock the starting block to write to
 @param data the data to write, it must be multiple of block size (can be taken from the card info that is coming with rfCardDetected call)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return number of bytes actually written or 0 if an error occured
 */
-(int)iso15693Write:(int)cardIndex startBlock:(int)startBlock data:(NSData *)data error:(NSError **)error;
/**
 Reads the security status of one more more blocks from ISO 15693 card.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param startBlock the starting block to read from
 @param nBlocks the number of blocks to get the security status
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return NSData object containing the data received or nil if an error occured
 */
-(NSData *)iso15693GetBlocksSecurityStatus:(int)cardIndex startBlock:(int)startBlock nBlocks:(int)nBlocks error:(NSError **)error;
/**
 Locks a single ISO 15693 card block. Locked blocks cannot be written upon anymore.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param block the block index to lock
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)iso15693LockBlock:(int)cardIndex block:(int)block error:(NSError **)error;
/**
 Changes ISO 15693 card AFI.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param afi new AFI value
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)iso15693WriteAFI:(int)cardIndex afi:(uint8_t)afi error:(NSError **)error;
/**
 Locks ISO 15693 AFI preventing further changes.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)iso15693LockAFI:(int)cardIndex error:(NSError **)error;
/**
 Changes ISO 15693 card DSFID.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param dsfid new DSFID value
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)iso15693WriteDSFID:(int)cardIndex dsfid:(uint8_t)dsfid error:(NSError **)error;
/**
 Locks ISO 15693 card DSFID preventing further changes.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)iso15693LockDSFID:(int)cardIndex error:(NSError **)error;

/**
 Initializes ISO1443B card and returns Answer To Select. Call this function before further communication with the card.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return Answer To Select data, or nil if command failed
 */
-(NSData *)iso14GetATS:(int)cardIndex error:(NSError **)error;

/**
 Executes APDU command on ISO1443B compatible card. The card must be initialized with iso14GetATS first
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param cla CLA parameter, refer to card documentation
 @param ins INS parameter, refer to card documentation
 @param p1 P1 parameter, refer to card documentation
 @param p2 P2 parameter, refer to card documentation
 @param data optional data with the command
 @param apduResult every APDU command sends 2 bytes result code, refer to card documentation
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return APDU response data or empty object, or nil if command failed
 */
-(NSData *)iso14APDU:(int)cardIndex cla:(uint8_t)cla ins:(uint8_t)ins p1:(uint8_t)p1 p2:(uint8_t)p2 data:(NSData *)data apduResult:(uint16_t *)apduResult error:(NSError **)error;

/**
 Executes APDU command on ISO1443 compatible card. The command supports both ISO14443-4 protocol and non-protocol cards. For the protocol activation you need to call iso14GetATS first
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param data command data
 @param status upon successful execution, the status of the command, returned by the card will be stored here. The status is meant as the first byte of the data, if you don't want it stripped out of the data, or the command you are sending does not send status byte, pass nil and the status byte will be ignored
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return command response data or nil if command failed
 */
-(NSData *)iso14Transceive:(int)cardIndex data:(NSData *)data status:(uint8_t *)status error:(NSError **)error;

/**
 Sets polling parameters of FeliCa card. Call this function before rfInit!
 @param requestCode request code, refer to FeliCa documentation, default is 1
 @param systemCode system code, refer to FeliCa documentation, default is 0xFFFF
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)felicaSetPollingParamsRequestCode:(int)requestCode systemCode:(int)systemCode error:(NSError **)error;

/**
 Executes a raw command on FeliCa card. The IDm(UUID) parameter is automatically added and needs to be skipped.
 @example To read block 0 with service code 0x0900, then you need to send command 06 with data 01 09 00 01 80 00
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param command command code, refer to FeliCa documentation
 @param data optional data to the command
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return NSData object containing the data received or nil if an error occured. Received data contains command code (1 byte) and command data, IDm(UUID) is skipped
 */
-(NSData *)felicaSendCommand:(int)cardIndex command:(int)command data:(NSData *)data error:(NSError **)error;

/**
 Reads one more more blocks of data from FeliCa card.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param serviceCode the service code, default is 0x0900
 @param startBlock the starting block to read from
 @param length the number of bytes to read, this must be multiple of block size (can be taken from the card info that is coming with rfCardDetected call)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return NSData object containing the data received or nil if an error occured
 */
-(NSData *)felicaRead:(int)cardIndex serviceCode:(int)serviceCode startBlock:(int)startBlock length:(int)length error:(NSError **)error;
/**
 Writes one more more blocks of data to FeliCa card.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param serviceCode the service code, default is 0x0900
 @param startBlock the starting block to write to
 @param data the data to write, it must be multiple of block size (can be taken from the card info that is coming with rfCardDetected call)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return number of bytes actually written or 0 if an error occured
 */
-(int)felicaWrite:(int)cardIndex serviceCode:(int)serviceCode startBlock:(int)startBlock data:(NSData *)data error:(NSError **)error;

/**
 Returns FeliCa SmartTag battery status
 @note Call this function before any other SmartTag
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param status upon successful execution, battery status will be returned here, one of FELICA_SMARTTAG_BATTERY_* constants
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)felicaSmartTagGetBatteryStatus:(int)cardIndex status:(int *)status error:(NSError **)error;
/**
 Clears the screen of FeliCa SmartTag
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)felicaSmartTagClearScreen:(int)cardIndex error:(NSError **)error;
/**
 Draws image on FeliCa SmartTag's screen. The screen is 200x96 pixels.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param image image to draw
 @param topLeftX - topleft X coordinate in pixels
 @param topLeftY - topleft Y coordinate in pixels
 @param drawMode draw mode, one of the FELICA_SMARTTAG_DRAW_* constants
 @param layout only used when drawMode is FELICA_SMARTTAG_DRAW_USE_LAYOUT, it specifies the index of the layout (1-12) of the previously stored image
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)felicaSmartTagDrawImage:(int)cardIndex image:(UIImage *)image topLeftX:(int)topLeftX topLeftY:(int)topLeftY drawMode:(int)drawMode layout:(int)layout error:(NSError **)error;
/**
 Saves the current display as layout number
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param layout layout index (1-12) to which the currently displayed image will be saved
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)felicaSmartTagSaveLayout:(int)cardIndex layout:(int)layout error:(NSError **)error;
/**
 Displays previously stored layout
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param layout layout index (1-12) of the previously stored image
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)felicaSmartTagDisplayLayout:(int)cardIndex layout:(int)layout error:(NSError **)error;
/**
 Writes data in FeliCa SmartTag.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param address the address of the card to write to, refer to SmartTag documentation
 @param data data to write, note that the data does not need to be aligned to block size
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return number of bytes actually written or 0 if an error occured
 */
-(int)felicaSmartTagWrite:(int)cardIndex address:(int)address data:(NSData *)data error:(NSError **)error;
/**
 Writes data in FeliCa SmartTag.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param address the address of the card to read from, refer to SmartTag documentation
 @param length of the data to read, note that the data does not need to be aligned to block size
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return NSData object containing the data received or nil if an error occured
 */
-(NSData *)felicaSmartTagRead:(int)cardIndex address:(int)address length:(int)length error:(NSError **)error;
/**
 Waits for FeliCa SmartTag to complete current operation. Waiting is generally not needed, but needed in case for example drawing an image and then saving the layout, you need to wait for the image to be drawn.
 Write operation forces waiting internally.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)felicaSmartTagWaitCompletion:(int)cardIndex error:(NSError **)error;

/**
 Reads one more more blocks of data from ST SRI card.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param address the starting block to read from
 @param length the number of bytes to read, this must be multiple of block size (can be taken from the card info that is coming with rfCardDetected call)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return NSData object containing the data received or nil if an error occured
 */
-(NSData *)stSRIRead:(int)cardIndex address:(int)address length:(int)length error:(NSError **)error;
/**
 Writes one more more blocks of data to ST SRI card.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param address the starting block to write to
 @param data the data to write, it must be multiple of block size (can be taken from the card info that is coming with rfCardDetected call)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return number of bytes actually written or 0 if an error occured
 */
-(int)stSRIWrite:(int)cardIndex address:(int)address data:(NSData *)data error:(NSError **)error;

@property (unsafe_unretained) id rfDelegate;
@end
