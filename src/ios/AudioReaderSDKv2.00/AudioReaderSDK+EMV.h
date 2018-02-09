#import "AudioReaderSDK.h"

/**
 * Definition of message processing result.
 */
/**
 * In [SEPA-FAST] this actual value is defined as NONE and used as initialization value. This
 * specification defines the value as OK indicator.
 */
#define PROCESSING_RESULT_OK 0x0000

/**
 * Set if the transaction is cancelled by the attendant or cardholder.
 */
#define PROCESSING_RESULT_CANCELLED 0x0001

/**
 * Set if the card returns a response code SW1 SW2 ë6A81í.
 */
#define PROCESSING_RESULT_CARD_BLOCKED 0x0002

/**
 * Set if the chip card is removed during chip processing.
 */
#define PROCESSING_RESULT_CARD_MISSING 0x0003

/**
 * Set if communication with the chip card does not work correctly (Only used in the commands
 * defined in section 7.1, not during transaction processing.)
 */
#define PROCESSING_RESULT_CHIP_ERROR 0x0004

/**
 * Set if duplicate data or incorrect TLV coding, data format, length or value is determined.
 */
#define PROCESSING_RESULT_DATA_ERROR 0x0005

/**
 * Set in Application Selection if the candidate list is empty.
 */
#define PROCESSING_RESULT_EMPTY_LIST 0x0006

/**
 * Set if SW1 SW2 ë6085í is received in response to the GPO command.
 */
#define PROCESSING_RESULT_GPO6985 0x0007

/**
 * Set if one (or more) mandatory card data object(s) have not been found.
 */
#define PROCESSING_RESULT_MISSING_DATA 0x0008

/**
 * Set if waiting for card insertion and timeout or another break occurs. (Only used in the
 * commands defined in section 7.1, not during transaction processing.)
 */
#define PROCESSING_RESULT_NO_CARD_INSERTED 0x0009

/**
 * Set if no Application Profile exists for the AID which was selected.
 */
#define PROCESSING_RESULT_NO_PROFILE 0x000A

/**
 * Set during Cardholder Application Confirmation.
 */
#define PROCESSING_RESULT_NOT_ACCEPTED 0x000B

/**
 * Set during PIN or data entry.
 */
#define PROCESSING_RESULT_TIMEOUT 0x000C

/**
 * Set if a technical error occurs during entry of data.
 */
#define PROCESSING_RESULT_ABORTED 0x000D

/**
 * Set during Pre-Processing for Non Chip if fallback transactions are not allowed.
 */
#define PROCESSING_RESULT_FALLBACK_PROHIBITED 0x000E

/**
 * Set when missing or inconsistent terminal configuration data is detected.
 */
#define PROCESSING_RESULT_CONFIGURATION_ERROR 0x000F

/**
 * Indicates that EMV.LIB has returned an error not handled by the reader firmware.
 */
#define PROCESSING_RESULT_EMV_LIB 0x8001

/**
 * Indicates that a function was called that is not allowed in the current state.
 */
#define PROCESSING_RESULT_FLOW_CONTROL  0x8002

/**
 * Indicates that processing was aborted due to internal errors.
 */
#define PROCESSING_RESULT_INTERNAL_ERROR  0x8003

/**
 * Indicates that reselection must be performed.
 */
#define PROCESSING_RESULT_RESELECT  0x8004

/**
 * Security error.
 */
#define PROCESSING_RESULT_SECURITY  0x8005

/**
 * Indicates that incorrect data has been received.
 */
#define PROCESSING_RESULT_INPUT_DATA_ERROR  0x8006

/**
 * Returned by the Reader to indicate that the transaction was aborted due to memory problems.
 */
#define PROCESSING_RESULT_OUT_OF_MEMORY  0x8007


#define READER_STATE_BORN 0x00
#define READER_STATE_CONFIGURATION_IN_PROGRESS 0x10
#define READER_STATE_IDLE 0x20
#define READER_STATE_SELECTION 0x21
#define READER_STATE_FINAL_SELECT 0x22
#define READER_STATE_CARD_HOLDER 0x30
#define READER_STATE_TRANSACTION 0x31
#define READER_STATE_PAN_CHECK 0x40
#define READER_STATE_ONLINE 0x50
#define READER_STATE_COMPLETION 0x51

#define TRANSACTION_DECLINED 0x00
#define TRANSACTION_AUTHORIZED 0x01
#define TRANSACTION_ABORTED 0x02
#define TRANSACTION_NOT_ACCEPTED 0x03
#define TRANSACTION_AUTHORIZED_SIGNATURE 0x81

/**
 * The class that represents reset parameters response data.
 */
@interface ResetParametersResponse : NSObject
/**
 * Processing result.
 */
@property (assign) int result;
/**
 * Reader state
 */
@property (assign) int state;
/**
 * Max configuration message size.
 */
@property (assign) int maxSize;

@end


@interface ConfigurationParametersResponse : NSObject
/**
 * Processing result.
 */
@property (assign) int result;
/**
 * Reader state
 */
@property (assign) int state;
/**
 * Configuration Data Set Version Number.
 */
@property (assign) int version;

/**
 * Max Configuration Message Size.
 */
@property (assign) int maxSize;

@end

/**
 * The class that represents load parameters response data.
 */
@interface LoadParametersResponse : NSObject
/**
 * Processing result.
 */
@property (assign) int result;
/**
 * Reader state
 */
@property (assign) int state;
/**
 * The accumulated amount of data already received.
 */
@property (assign) int dataReceived;

@end


@interface TransactionResponse : NSObject
/**
 * Processing result.
 */
@property (assign) int result;
/**
 * Reader state
 */
@property (assign) int state;
/**
 * Configuration Data Set Version Number.
 */
@property (assign) int version;
/**
 * Max Configuration Message Size.
 */
@property (assign) int maxSize;

/**
 * All tags as data object
 */
@property (copy) NSData *allTags;

/**
 Helper function: parses and returns processing result
 */
-(int)getProcessingResult;
/**
 Helper function: parses and returns transaction result
 */
-(int)getTransactionResult;
/**
 Helper function: checks if the transaction was approved with signature
 */
-(bool)isSignatureRequired;
@end



@protocol EMVProcessorDelegate <NSObject>

-(NSData *)onCardHolderSelectionRequest:(NSData *)data;

-(NSData *)onPanCheckingRequest:(NSData *)data;

-(NSData *)onOnlineProcessingRequest:(NSData *)data;

-(void)onConfirmOrReverseOnlineRequest:(NSData *)data;
@end

@interface AudioSmartCardReader (EMV)

-(void)emvSetRSADecryptionKey:(NSData *)key module:(NSData *)module;
-(ResetParametersResponse *)emvResetParameters:(NSError **)error;
-(LoadParametersResponse *)emvLoadParameters:(NSData *)parameters chunkSize:(int)chunkSize error:(NSError **)error;
-(ConfigurationParametersResponse *)emvGetConfigurationParameters:(NSError **)error;
-(TransactionResponse *)emvInitProcessingWithData:(NSData *)data error:(NSError **)error;


@property (unsafe_unretained) id emvDelegate;
@end
