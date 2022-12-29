#ifndef ASTROUART_OPCODES_ID_H
#define ASTROUART_OPCODES_ID_H

typedef enum astronode_op_code
{
    ASTRONODE_OP_CODE_ADC_RA = 0xe4,
    ASTRONODE_OP_CODE_ADC_RR = 0x64,
    ASTRONODE_OP_CODE_CFG_FA = 0x91,
    ASTRONODE_OP_CODE_CFG_FR = 0x11,
    ASTRONODE_OP_CODE_CFG_RA = 0x95,
    ASTRONODE_OP_CODE_CFG_RR = 0x15,
    ASTRONODE_OP_CODE_CFG_SA = 0x90,
    ASTRONODE_OP_CODE_CFG_SR = 0x10,
    ASTRONODE_OP_CODE_CFG_WA = 0x85,
    ASTRONODE_OP_CODE_CFG_WR = 0x05,
    ASTRONODE_OP_CODE_CTX_SA = 0xe6,
    ASTRONODE_OP_CODE_CTX_SR = 0x66,
    ASTRONODE_OP_CODE_DGI_RA = 0x99,
    ASTRONODE_OP_CODE_DGI_RR = 0x19,
    ASTRONODE_OP_CODE_DSN_RA = 0x9a,
    ASTRONODE_OP_CODE_DSN_RR = 0x1a,
    ASTRONODE_OP_CODE_END_RA = 0xeb,
    ASTRONODE_OP_CODE_END_RR = 0x6b,
    ASTRONODE_OP_CODE_NCO_RA = 0x98,
    ASTRONODE_OP_CODE_NCO_RR = 0x18,
    ASTRONODE_OP_CODE_ERROR  = 0xff,
    ASTRONODE_OP_CODE_EVT_RA = 0xe5,
    ASTRONODE_OP_CODE_EVT_RR = 0x65,
    ASTRONODE_OP_CODE_GEO_WA = 0xb5,
    ASTRONODE_OP_CODE_GEO_WR = 0x35,
    ASTRONODE_OP_CODE_GPI_RA = 0xe3,
    ASTRONODE_OP_CODE_GPI_RR = 0x63,
    ASTRONODE_OP_CODE_GPO_SA = 0xe2,
    ASTRONODE_OP_CODE_GPO_SR = 0x62,
    ASTRONODE_OP_CODE_LCD_RA = 0xea,
    ASTRONODE_OP_CODE_LCD_RR = 0x6a,
    ASTRONODE_OP_CODE_MPN_RA = 0x9b,
    ASTRONODE_OP_CODE_MPN_RR = 0x1b,
    ASTRONODE_OP_CODE_MST_RA = 0xe9,
    ASTRONODE_OP_CODE_MST_RR = 0x69,
    ASTRONODE_OP_CODE_PER_CA = 0xe8,
    ASTRONODE_OP_CODE_PER_CR = 0x68,
    ASTRONODE_OP_CODE_PER_RA = 0xe7,
    ASTRONODE_OP_CODE_PER_RR = 0x67,
    ASTRONODE_OP_CODE_PLD_DA = 0xa6,
    ASTRONODE_OP_CODE_PLD_DR = 0x26,
    ASTRONODE_OP_CODE_PLD_EA = 0xa5,
    ASTRONODE_OP_CODE_PLD_ER = 0x25,
    ASTRONODE_OP_CODE_PLD_FA = 0xa7,
    ASTRONODE_OP_CODE_PLD_FR = 0x27,
    ASTRONODE_OP_CODE_RES_CA = 0xd5,
    ASTRONODE_OP_CODE_RES_CR = 0x55,
    ASTRONODE_OP_CODE_RTC_RA = 0x97,
    ASTRONODE_OP_CODE_RTC_RR = 0x17,
    ASTRONODE_OP_CODE_SAK_CA = 0xc6,
    ASTRONODE_OP_CODE_SAK_CR = 0x46,
    ASTRONODE_OP_CODE_SAK_RA = 0xc5,
    ASTRONODE_OP_CODE_SAK_RR = 0x45,
    ASTRONODE_OP_CODE_SSC_WA = 0x87,
    ASTRONODE_OP_CODE_SSC_WR = 0x07,
    ASTRONODE_OP_CODE_WIF_WA = 0x86,
    ASTRONODE_OP_CODE_WIF_WR = 0x06,
    ASTRONODE_OP_CODE_CMD_CA = 0xc8,
    ASTRONODE_OP_CODE_CMD_CR = 0x48,
    ASTRONODE_OP_CODE_CMD_RA = 0xc7,
    ASTRONODE_OP_CODE_CMD_RR = 0x47,
    ASTRONODE_OP_CODE_VAL_WR = 0x60,
    ASTRONODE_OP_CODE_VAL_WA = 0xe0,
    ASTRONODE_OP_CODE_TTX_SR = 0x61,
    ASTRONODE_OP_CODE_TTX_SA = 0xe1,
    AI_OPCODE_DEBUG  = 0x01,
} astronode_op_code;

typedef enum debug_sub_opcodes
{
    DEBUG_OPCODE_SET_SYS_TIME          = 0x01,
    DEBUG_OPCODE_SHIFT_MONO_COUNTER    = 0x03,
    DEBUG_OPCODE_GET_MONO_COUNTER      = 0x04,
    DEBUG_OPCODE_SET_EPHEMERIS         = 0x05,
    DEBUG_OPCODE_GET_EPHEMERIS         = 0x06,
    DEBUG_OPCODE_SET_LAST_SYNC_MONO    = 0x07,
    DEBUG_OPCODE_GET_LAST_SYNC_MONO    = 0x08,
    DEBUG_OPCODE_GET_ALARM_MONO        = 0x09,
    DEBUG_OPCODE_SET_POLLING_PERIOD    = 0x0A,
    DEBUG_OPCODE_SET_SAT_SEARCH_PERIOD = 0x0B,
    DEBUG_OPCODE_ENA_TEST_SAT          = 0x0C,
    DEBUG_OPCODE_ENA_SECURITY_CHECKS   = 0x0D,
    DEBUG_OPCODE_FAKE_HMAC_FAILURE     = 0x0E,
    DEBUG_OPCODE_SET_RX_SEARCH_FREQS   = 0x0F,
    DEBUG_OPCODE_RESET                 = 0x10,
    DEBUG_OPCODE_SET_PRIO              = 0x11,
    DEBUG_OPCODE_SKIP_SAT_ACKS         = 0x12,
    DEBUG_OPCODE_READ_EEPROM           = 0x13,
    DEBUG_OPCODE_SET_EEPROM            = 0x14,
    DEBUG_OPCODE_DISABLE_RETRY_RAND    = 0x15,
}debug_sub_opcodes;

struct astronode_answer_t{
    uint8_t answer_id;
    std::vector<uint8_t> answer_parameters;
    uint16_t answer_checksum;
    uint8_t error_code; // serial port error code
};

#endif //ASTROUART_OPCODES_ID_H
