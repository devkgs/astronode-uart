#ifndef ASTROUART_APPLICATION_UTILS_H
#define ASTROUART_APPLICATION_UTILS_H

#include <vector>
#include <cstdint>

 // TODO use another way to hide the utils:
 /* DO something like this:
 class Hidden
{
  private:
    friend class Exposed;
    Hidden() {}
    int hidden_x;
};

class Exposed : private Hidden
{
  public:
    Exposed() : Hidden() {}
    void DoStuff() { printf( "%d" , hidden_x ); }
};
  */

class Application_utils {
public:
   // bool get_answer_success(std::vector<uint8_t> frame);
//    uint8_t get_answer_id(std::vector<uint8_t> frame);
//    std::vector<uint8_t> get_answer_parameters(std::vector<uint8_t> frame);



    typedef enum astronode_error_code
    {
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
        ASTRONODE_ERR_CODE_NO_CLEAR             = 0x4601
    } astronode_error_code_t;

};


#endif //ASTROUART_APPLICATION_UTILS_H
