#ifndef ASTROUART_COMMAND_H
#define ASTROUART_COMMAND_H

#endif //ASTROUART_COMMAND_H

#include <vector>
#include <cstdint>
#include <iostream>

#include "Transport_layer.h"

class Application_layer{
public:
    Application_layer(std::shared_ptr<Transport_layer> tr);
    virtual void request_cmd(const std::vector<uint8_t> command);
    virtual bool get_answer_success();
    virtual std::vector<uint8_t> get_answer_parameters(void);
    virtual ~Application_layer() {};//= default;
    std::shared_ptr<Transport_layer> tr_;
private:
    bool request_sent = false;
    int val_;
    uint8_t command_id_;
    std::vector<uint8_t> decoded_answer_;

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
    void request_cmd(std::string lat, std::string lng); // ex: lat = "465343400" for 46.53434
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