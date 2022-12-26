#ifndef ASTROUART_ASTRONODE_COMMAND_H
#define ASTROUART_ASTRONODE_COMMAND_H

#include <vector>
#include <cstdint>
#include "Transport_layer.h"

class Astronode_command {
#define SSID_LENGTH 33
#define PASSWORD_LENGTH 64
#define TOKEN_LENGTH 97
public:
    typedef enum astronode_error_code
    {
        ASTRONODE_ERR_CODE_OK                   = 0x0000,
        ASTRONODE_ERR_CODE_CRC_NOT_VALID        = 0x0001,
        ASTRONODE_ERR_CODE_LENGTH_NOT_VALID     = 0x0011,
        ASTRONODE_ERR_CODE_OPCODE_NOT_VALID     = 0x0121,
        ASTRONODE_ERR_CODE_FORMAT_NOT_VALID     = 0x0601,
        ASTRONODE_ERR_CODE_FLASH_WRITING_FAILED = 0x0611,
        ASTRONODE_ERR_CODE_BUFFER_FULL          = 0x2501,
        ASTRONODE_ERR_CODE_DUPLICATE_ID         = 0x2511,
        ASTRONODE_ERR_CODE_BUFFER_EMPTY         = 0x2601,
        ASTRONODE_ERR_CODE_INVALID_POS          = 0x3501,
        ASTRONODE_ERR_CODE_NO_ACK               = 0x4501,
        ASTRONODE_ERR_CODE_NO_CLEAR             = 0x4601,
    } astronode_error_code_t;

    // Common
    astronode_error_code get_answer_error_code(Transport_layer::answer_t ans);

    // CFG_W
    std::vector<uint8_t>  cfg_w_build_command(uint8_t payload_ack_bit, uint8_t add_geo_bit, uint8_t enable_ephemeris_bit, uint8_t deep_sleep_enabled_bit, uint8_t payload_ack_evt_pin_bit, uint8_t reset_notif_evt_pin_bit);
    // WIF_W
    std::vector<uint8_t> wif_w_build_command(std::string wlan_ssid, std::string wlan_key, std::string auth_token);
    // SSC_W
    std::vector<uint8_t> ssc_w_build_command(uint8_t sat_period_enum, uint8_t enable_search);
    // CFG_S
    std::vector<uint8_t> cfg_s_build_command(void);
    // CFG_F
    std::vector<uint8_t> cfg_f_build_command(void);
    // CFG_R
    std::vector<uint8_t> cfg_r_build_command(void);
    uint8_t cfg_r_get_product_id(std::vector<uint8_t> astronode_answer);
    uint8_t cfg_r_get_hardware_revision(std::vector<uint8_t> astronode_answer);
    uint8_t cfg_r_get_firmware_major_version(std::vector<uint8_t> astronode_answer);
    uint8_t cfg_r_get_firmware_minor_version(std::vector<uint8_t> astronode_answer);
    uint8_t cfg_r_get_firmware_revision(std::vector<uint8_t> astronode_answer);
    bool cfg_r_get_payload_ack(std::vector<uint8_t> astronode_answer);
    bool cfg_r_get_add_geolocation(std::vector<uint8_t> astronode_answer);
    bool cfg_r_get_ephemeris_enabled(std::vector<uint8_t> astronode_answer);
    bool cfg_r_get_deep_sleep_enabled(std::vector<uint8_t> astronode_answer);
    bool cfg_r_get_payload_ack_evt_pin_enabled(std::vector<uint8_t> astronode_answer);
    bool cfg_r_get_reset_notification_evt_pin_enabled(std::vector<uint8_t> astronode_answer);
    bool cfg_r_get_command_available_evt_pin_enabled(std::vector<uint8_t> astronode_answer);
    bool cfg_r_get_message_transmission_pending_evt_pin_enabled(std::vector<uint8_t> astronode_answer);
    // ...


};


#endif //ASTROUART_ASTRONODE_COMMAND_H
