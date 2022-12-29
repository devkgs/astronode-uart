#ifndef ASTROUART_COMMAND_H
#define ASTROUART_COMMAND_H

#endif //ASTROUART_COMMAND_H

#include <vector>
#include <cstdint>
#include <iostream>

#include "Transport_layer.h"
#include "Opcodes_id.h"

class Application_layer{
public:

    struct command_answer_t{
        uint8_t id;
        std::vector<uint8_t> parameters;
        uint8_t error_code;
    };

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

    Application_layer(std::shared_ptr<Transport_layer> tr);
    virtual void request_cmd(const std::vector<uint8_t> command);
    virtual astronode_error_code get_answer_error_code();
    virtual Transport_layer::serial_port_error_code get_serial_port_error_code();
    virtual std::vector<uint8_t> get_answer_parameters(void);
    virtual ~Application_layer() {};//= default;
    std::shared_ptr<Transport_layer> tr_;

private:
    bool request_sent_ = false;
    uint8_t command_id_sent_;
    std::vector<uint8_t> decoded_answer_parameters_;
    uint8_t decoded_answer_command_id_;
    uint16_t decoded_answer_checksum_;
    uint8_t transport_layer_error_;
};

class Command_cfg_w : public Application_layer{
public:
    Command_cfg_w(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(uint8_t payload_ack_bit, uint8_t add_geo_bit, uint8_t enable_ephemeris_bit, uint8_t deep_sleep_enabled_bit, uint8_t payload_ack_evt_pin_bit, uint8_t reset_notif_evt_pin_bit);
};

class Command_wif_w : public Application_layer{
public:
    Command_wif_w(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(std::string wlan_ssid, std::string wlan_key, std::string auth_token);
#define SSID_LENGTH 33
#define PASSWORD_LENGTH 64
#define TOKEN_LENGTH 97
};

class Command_ssc_w : public Application_layer{
public:
    Command_ssc_w(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(uint8_t sat_period_enum, uint8_t enable_search);
};

class Command_cfg_s : public Application_layer{
public:
    Command_cfg_s(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
};

class Command_cfg_f : public Application_layer{
public:
    Command_cfg_f(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
};

class Command_cfg_r : public Application_layer{
public:
    Command_cfg_r(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
    //std::vector<uint8_t> get_answer_parameters(void);
    uint8_t get_product_id(void);               // TODO add method content
    uint8_t get_hardware_revision(void);        // TODO add method content
    uint8_t get_firmware_major_version(void);   // TODO add method content
    uint8_t get_firmware_minor_version(void);   // TODO add method content
    uint8_t get_firmware_revision(void);        // TODO add method content
    bool get_payload_ack(void);                 // TODO add method content
    bool get_add_geolocation(void);             // TODO add method content
    bool get_ephemeris_enabled(void);           // TODO add method content
    bool get_deep_sleep_enabled(void);          // TODO add method content
    bool get_payload_ack_evt_pin_enabled(void); // TODO add method content
    bool get_reset_notification_evt_pin_enabled(void);              // TODO add method content
    bool get_command_available_evt_pin_enabled(void);               // TODO add method content
    bool get_message_transmission_pending_evt_pin_enabled(void);    // TODO add method content
};

class Command_rtc_r : public Application_layer{
public:
    Command_rtc_r(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
  //  std::vector<uint8_t> get_answer_parameters(void);
    uint32_t get_rtc_time(void); // TODO add method content
};

class Command_nco_r : public Application_layer{
public:
    Command_nco_r(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
  //  std::vector<uint8_t> get_answer_parameters(void);
    uint32_t get_time_to_next_pass(void);   // TODO add method content
};

class Command_mgi_r : public Application_layer{
public:
    Command_mgi_r(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
};

class Command_msn_r : public Application_layer{
public:
    Command_msn_r(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
};

class Command_mpn_r : public Application_layer{
public:
    Command_mpn_r(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
};

class Command_pld_e : public Application_layer{
public:
    Command_pld_e(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(uint16_t payload_id, const std::string payload_data);
    uint16_t get_command_id(void);
};

class Command_pld_d : public Application_layer{
public:
    Command_pld_d(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
    uint16_t get_command_id(void);
};

class Command_pld_f : public Application_layer{
public:
    Command_pld_f(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);

};

class Command_geo_w : public Application_layer{
public:
    Command_geo_w(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(int32_t lat, int32_t lng); // ex: lat = 465343400 for 46.53434
};

class Command_evt_r : public Application_layer{
public:
    Command_evt_r(std::shared_ptr<Transport_layer> tr): Application_layer(tr){}
    void request_cmd(void);
    bool get_sak_available(void);
    bool get_module_reset(void);
    bool get_command_available(void);
    bool get_message_transmit_pending(void);
};

class Command_sak_r : public Application_layer{
public:
    Command_sak_r(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
    uint16_t get_command_id(void);
};

class Command_sak_c : public Application_layer{
public:
    Command_sak_c(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
};

class Command_cmd_r : public Application_layer{
public:
    Command_cmd_r(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
    uint32_t get_created_date(void);
    std::vector<uint8_t> get_payload(void);
};

class Command_cmd_c : public Application_layer{
public:
    Command_cmd_c(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
};

class Command_res_c : public Application_layer{
public:
    Command_res_c(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
};

class Command_val_w : public Application_layer{
public:
    Command_val_w(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
};

class Command_ttx_s : public Application_layer{
public:
    Command_ttx_s(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(uint8_t transmit_duration_sec);
};

class Command_manufacturing_asic_power_on : public Application_layer{
public:
    Command_manufacturing_asic_power_on(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
};

class Command_manufacturing_tx_continuous : public Application_layer{
public:
    Command_manufacturing_tx_continuous(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
};

class Command_homologation_auto_tx : public Application_layer{
public:
    Command_homologation_auto_tx(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
};

class Command_homologation_stop_auto_tx : public Application_layer{
public:
    Command_homologation_stop_auto_tx(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
};

class Command_homologation_start_duty_cycle_mode : public Application_layer{
public:
    Command_homologation_start_duty_cycle_mode(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
};

class Command_homologation_start_continuous_mode : public Application_layer {
public:
    Command_homologation_start_continuous_mode(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
};

class Command_unknown : public Application_layer{
public:
    Command_unknown(std::shared_ptr<Transport_layer> tr) : Application_layer(tr){}
    void request_cmd(void);
};
