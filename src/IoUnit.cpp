#include "../lib/IoUnit.h"
#include <iostream>

IoUnit::IoUnit()
{
}

uint8_t IoUnit::read(uint8_t local_address)
{
    // ông chủ xưởng sản xuất hỏi là có hàng nhập khẩu về
    // không bác cổng thương mại
    if (local_address == STATUS_REGISTER)
    {
        // bác cổng thương mại đi kiểm tra hàng trên
        // máy tính xem có không
        // có thì báo lại ông chủ
        // không thì hỏi ông là không có ông đỡ mất công
        // hỏi người ra đứng chờ đợi chở hàng về
        return is_key_available() ? 1 : 0;
    }

    // nếu thư yêu cầu bảo là kiểm tra hiện tại
    // là hàng gì để trở về sau khi đã biết là có hàng
    // "cổng thương mại" vẫn vào kho một lần nữa để kiểm tra xem có
    // hàng chuẩn không
    if (local_address != KEY_DATA_REGISTER || !is_key_available())
    {
        return 0;
    }

    // nếu có hàng + và nhận được yêu cầu là sắp sẵn hàng ra
    // để anh hỏi thằng cu giao hàng , nó lấy hàng về
    // sau đó cổng thương mại lấy hàng từ ống 1 chiều ra để sẵn
    // ở bãi tí thằng cu em giao hàng trong nước nó đến thì tự bốc lên
    uint8_t key = key_queue.front();
    key_queue.pop();
    return key;
}

bool IoUnit::is_key_available() const
{
    // cổng thương mại , kiêm tra ở ống một chiều 
    // có hàng nhập khẩu không
    return !key_queue.empty();
}

void IoUnit::push_key_input(uint8_t key)
{
    // nếu mà bên nước ngoài , giao hàng về
    // thì cổng thương mại
    // cất vào ống 1 chiều
    key_queue.push(key);
}

void IoUnit::write(uint8_t local_address, uint8_t value)
{
    // khi mà ông chủ xưởng sản xuất
    // báo là ông có một lô hàng xuất quốc tế
    // và cổng công thương xác minh đúng là 
    // giao hàng quốc tế
    if (local_address != OUTPUT_REGISTER)
    {
        return;
    }

    // chuyển bị tàu để cho hàng lên và mang đi 
    // sang nước bạn
    std::cout << static_cast<char>(value);
}