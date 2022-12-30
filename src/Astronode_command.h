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

    Astronode_command(std::shared_ptr<Transport_layer> tr);
    // Common
    astronode_error_code get_answer_error_code(astronode_answer_t ans);
    // CFG_W
    astronode_answer_t cfg_w(uint8_t payload_ack_bit, uint8_t add_geo_bit, uint8_t enable_ephemeris_bit, uint8_t deep_sleep_enabled_bit, uint8_t payload_ack_evt_pin_bit, uint8_t reset_notif_evt_pin_bit);
    // WIF_W
    astronode_answer_t wif_w(std::string wlan_ssid, std::string wlan_key, std::string auth_token);
    // SSC_W
    astronode_answer_t ssc_w(uint8_t sat_period_enum, uint8_t enable_search);
    // CFG_S
    astronode_answer_t cfg_s(void);
    // CFG_F
    astronode_answer_t cfg_f(void);
    // CFG_R
    astronode_answer_t cfg_r(void);
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
    // RTC_R
    astronode_answer_t rtc_r(void);
    uint32_t rtc_r_get_rtc_time(std::vector<uint8_t> astronode_answer);
    // NCO_R
    astronode_answer_t nco_r(void);
    uint32_t nco_r_get_time_to_next_pass(std::vector<uint8_t> astronode_answer);
    // MGI_R
    astronode_answer_t mgi_r(void);
    // MSN_R
    astronode_answer_t msn_r(void);
    // MPN_R
    astronode_answer_t mpn_r(void);
    // PLD_E
    astronode_answer_t pld_e(uint16_t payload_id, const std::string payload_data);
    uint16_t pld_e_get_payload_id(std::vector<uint8_t> astronode_answer);
    // PLD_D
    astronode_answer_t pld_d(void);
    uint16_t pld_d_get_payload_id(std::vector<uint8_t> astronode_answer);
    // PLD_F
    astronode_answer_t pld_f(void);
    // GEO_W
    astronode_answer_t geo_w(int32_t lat, int32_t lng); // ex: lat = 465343400 for 46.53434
    // EVT_R
    astronode_answer_t evt_r(void);
    bool evt_r_get_sak_available(std::vector<uint8_t> astronode_answer);
    bool evt_r_get_module_reset(std::vector<uint8_t> astronode_answer);
    bool evt_r_get_command_available(std::vector<uint8_t> astronode_answer);
    bool evt_r_get_message_transmit_pending(std::vector<uint8_t> astronode_answer);
    // SAK_R
    astronode_answer_t sak_r(void);
    uint16_t sak_r_get_payload_id(std::vector<uint8_t> astronode_answer);
    // SAK_C
    astronode_answer_t sak_c(void);
    // CMD_R
    astronode_answer_t cmd_r(void);
    uint32_t cmd_r_get_created_date(std::vector<uint8_t> astronode_answer);
    std::vector<uint8_t> cmd_r_get_payload(std::vector<uint8_t> astronode_answer);
    // CMD_C
    astronode_answer_t cmd_c(void);
    // RES_C
    astronode_answer_t res_c(void);
    // VAL_W
    astronode_answer_t val_w(void);
    // TTX_S
    astronode_answer_t ttx_s(uint8_t transmit_duration_sec);

private:
    std::shared_ptr<Transport_layer> tr_;
};


#endif //ASTROUART_ASTRONODE_COMMAND_H
