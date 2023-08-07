/* 
 * File:   application.c
 * Author: Mohamed Saker
 * https://www.linkedin.com/in/mohamed-saker-795123228/
 */
#include "application.h"
#include "MCAL_Layer/ADC/hal_adc.h"
#include "MCAL_Layer/usart/hal_usart.h"
void welcome_massege(void);

void EUSART_TxDefaultInterruptHandler(void)
{
    
}


chr_lcd_4bit_t lcd ={
  .lcd_rs.port = PORTC_INDEX,
  .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
  .lcd_rs.pin = GPIO_PIN0,
  .lcd_rs.logic = GPIO_LOW,
  .lcd_en.port = PORTC_INDEX,
  .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
  .lcd_en.pin = GPIO_PIN1,
  .lcd_en.logic = GPIO_LOW,
  .lcd_data[0].port = PORTC_INDEX,
  .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[0].pin = GPIO_PIN2,
  .lcd_data[0].logic = GPIO_LOW,
  .lcd_data[1].port = PORTC_INDEX,
  .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[1].pin = GPIO_PIN3,
  .lcd_data[1].logic = GPIO_LOW,
  .lcd_data[2].port = PORTC_INDEX,
  .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[2].pin = GPIO_PIN4,
  .lcd_data[2].logic = GPIO_LOW,
  .lcd_data[3].port = PORTC_INDEX,
  .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[3].pin = GPIO_PIN5,
  .lcd_data[3].logic = GPIO_LOW,
};

keypad_t keypad = {
  .keypad_row_pins[0].port = PORTB_INDEX,
  .keypad_row_pins[0].direction = GPIO_DIRECTION_OUTPUT,
  .keypad_row_pins[0].pin = GPIO_PIN0,
  .keypad_row_pins[0].logic = GPIO_LOW,
  .keypad_row_pins[1].port = PORTB_INDEX,
  .keypad_row_pins[1].direction = GPIO_DIRECTION_OUTPUT,
  .keypad_row_pins[1].pin = GPIO_PIN1,
  .keypad_row_pins[1].logic = GPIO_LOW,
  .keypad_row_pins[2].port = PORTB_INDEX,
  .keypad_row_pins[2].direction = GPIO_DIRECTION_OUTPUT,
  .keypad_row_pins[2].pin = GPIO_PIN2,
  .keypad_row_pins[2].logic = GPIO_LOW,
  .keypad_row_pins[3].port = PORTB_INDEX,
  .keypad_row_pins[3].direction = GPIO_DIRECTION_OUTPUT,
  .keypad_row_pins[3].pin = GPIO_PIN3,
  .keypad_row_pins[3].logic = GPIO_LOW,
  .keypad_columns_pins[0].port = PORTB_INDEX,
  .keypad_columns_pins[0].direction = GPIO_DIRECTION_INPUT,
  .keypad_columns_pins[0].pin = GPIO_PIN4,
  .keypad_columns_pins[0].logic = GPIO_LOW,
  .keypad_columns_pins[1].port = PORTB_INDEX,
  .keypad_columns_pins[1].direction = GPIO_DIRECTION_INPUT,
  .keypad_columns_pins[1].pin = GPIO_PIN5,
  .keypad_columns_pins[1].logic = GPIO_LOW,
  .keypad_columns_pins[2].port = PORTB_INDEX,
  .keypad_columns_pins[2].direction = GPIO_DIRECTION_INPUT,
  .keypad_columns_pins[2].pin = GPIO_PIN6,
  .keypad_columns_pins[2].logic = GPIO_LOW,
  .keypad_columns_pins[3].port = PORTB_INDEX,
  .keypad_columns_pins[3].direction = GPIO_DIRECTION_INPUT,
  .keypad_columns_pins[3].pin = GPIO_PIN7,
  .keypad_columns_pins[3].logic = GPIO_LOW,
};

usart_t uart = {
  .baudrate = 9600,
  .baudrate_gen_gonfig = BAUDRATE_ASYN_8BIT_lOW_SPEED,
  
  .usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE,
  .usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE,
  .usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE,
  
  .usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE,
  .usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE,
  .usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE,
  
  .EUSART_TxDefaultInterruptHandler = NULL,
  .EUSART_RxDefaultInterruptHandler = NULL,
  .EUSART_FramingErrorHandler = NULL,
  .EUSART_OverrunErrorHandler = NULL,
};



uint8 pass_code[] = {'1', '2', '3', '4', '5'};
uint8 all_value[5];
uint8 keypad_value = 0;
uint8 index = 0;


int main() { 
    Std_ReturnType ret = E_NOT_OK;
    
    application_intialize();
//    welcome_massege();
    __delay_ms(100);
    ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
    ret = lcd_4bit_send_string_pos(&lcd, 1, 1, "Enter Pass: ");

    
    
        
    
    
    
    while (1) {

        ret = keypad_get_value(&keypad, &keypad_value);
        __delay_ms(200);

        if ((keypad_value != '\0') && (keypad_value != '=') && (keypad_value != '#')) {
            
            ret = lcd_4bit_send_string_pos(&lcd, 2, index, "*");
            
            all_value[index] = '\0';
            all_value[index++] = keypad_value;
            keypad_value = '\0';

        }
        else if(keypad_value == '=')
        {
            
            if(strcmp(pass_code, all_value) == 0)
            {
                
                ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
                ret = lcd_4bit_send_string_pos(&lcd, 1, 1, "Welcome!!!");
                __delay_ms(1000);
                ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
                loop:
                ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
                ret = lcd_4bit_send_string_pos(&lcd, 1, 1, "Room1 : 1");
                ret = lcd_4bit_send_string_pos(&lcd, 2, 1, "Room2 : 2");
                ret = lcd_4bit_send_string_pos(&lcd, 3, 1, "Room3 : 3");
                ret = lcd_4bit_send_string_pos(&lcd, 4, 1, "Room4 : 4");
                ret = lcd_4bit_send_string_pos(&lcd, 1, 14, "AC : 5");
                ret = lcd_4bit_send_string_pos(&lcd, 2, 14, "TV : 6");
                
                
              
                 do {
                    ret = keypad_get_value(&keypad, &keypad_value);
                    if ('1' == keypad_value) //Room1
                    {
                        ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
                        ret = lcd_4bit_send_string_pos(&lcd, 1, 1, "Turn On :2");
                        ret = lcd_4bit_send_string_pos(&lcd, 2, 1, "Turn OFF :3");
                        ret = lcd_4bit_send_string_pos(&lcd, 3, 1, "Back : -");
                        do {
                            ret = keypad_get_value(&keypad, &keypad_value);
                            if (keypad_value == '-') {
                                goto loop;
                            }
                            else if(keypad_value == '2')
                            {
                                ret = EUSART_ASYNC_WriteByteBlocking('a');
                            }
                            else if(keypad_value == '3')
                            {
                                ret = EUSART_ASYNC_WriteByteBlocking('b');
                            }
                        } while (keypad_value != '#');

                    } else if (keypad_value == '2') //Room2
                    {
                        ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
                        ret = lcd_4bit_send_string_pos(&lcd, 1, 1, "Turn On :3");
                        ret = lcd_4bit_send_string_pos(&lcd, 2, 1, "Turn OFF :4");
                        ret = lcd_4bit_send_string_pos(&lcd, 3, 1, "Back : -");

                        do {
                            ret = keypad_get_value(&keypad, &keypad_value);
                            if (keypad_value == '-') {
                                goto loop;
                            }
                            else if(keypad_value == '3')
                            {
                                ret = EUSART_ASYNC_WriteByteBlocking('c');
                            }
                            else if(keypad_value == '4')
                            {
                                ret = EUSART_ASYNC_WriteByteBlocking('d');
                            }
                        } while (keypad_value != '#');
                    } else if (keypad_value == '3') //Room3
                    {
                        ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
                        ret = lcd_4bit_send_string_pos(&lcd, 1, 1, "Turn On :1");
                        ret = lcd_4bit_send_string_pos(&lcd, 2, 1, "Turn OFF :2");
                        ret = lcd_4bit_send_string_pos(&lcd, 3, 1, "Back : -");

                        do {
                            ret = keypad_get_value(&keypad, &keypad_value);
                            if (keypad_value == '-') {
                                goto loop;
                            }
                            else if(keypad_value == '1')
                            {
                                ret = EUSART_ASYNC_WriteByteBlocking('e');
                            }
                            else if(keypad_value == '2')
                            {
                                ret = EUSART_ASYNC_WriteByteBlocking('f');
                            }
                        } while (keypad_value != '#');
                    } else if (keypad_value == '4') //Room4
                    {
                        ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
                        ret = lcd_4bit_send_string_pos(&lcd, 1, 1, "Turn On :2");
                        ret = lcd_4bit_send_string_pos(&lcd, 2, 1, "Turn OFF :3");
                        ret = lcd_4bit_send_string_pos(&lcd, 3, 1, "Back : -");

                        do {
                            ret = keypad_get_value(&keypad, &keypad_value);
                            if (keypad_value == '-') {
                                goto loop;
                            }
                            else if(keypad_value == '2')
                            {
                                ret = EUSART_ASYNC_WriteByteBlocking('g');
                            }
                            else if(keypad_value == '3')
                            {
                                ret = EUSART_ASYNC_WriteByteBlocking('h');
                            }
                        } while (keypad_value != '#');
                    } else if (keypad_value == '5') //A/C
                    {
                        ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
                        ret = lcd_4bit_send_string_pos(&lcd, 1, 1, "Turn On :2");
                        ret = lcd_4bit_send_string_pos(&lcd, 2, 1, "Turn OFF :3");
                        ret = lcd_4bit_send_string_pos(&lcd, 3, 1, "Back : -");

                        do {
                            ret = keypad_get_value(&keypad, &keypad_value);
                            if (keypad_value == '-') {
                                goto loop;
                            }
                            else if(keypad_value == '2')
                            {
                                ret = EUSART_ASYNC_WriteByteBlocking('i');
                            }
                            else if(keypad_value == '3')
                            {
                                ret = EUSART_ASYNC_WriteByteBlocking('j');
                            }
                        } while (keypad_value != '#');
                    } else if (keypad_value == '6') //TV
                    {
                        ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
                        ret = lcd_4bit_send_string_pos(&lcd, 1, 1, "Turn On :2");
                        ret = lcd_4bit_send_string_pos(&lcd, 2, 1, "Turn OFF :3");
                        ret = lcd_4bit_send_string_pos(&lcd, 3, 1, "Back : -");

                        do {
                            ret = keypad_get_value(&keypad, &keypad_value);
                            if (keypad_value == '-') {
                                goto loop;
                            }
                            else if(keypad_value == '2')
                            {
                                ret = EUSART_ASYNC_WriteByteBlocking('k');
                            }
                            else if(keypad_value == '3')
                            {
                                ret = EUSART_ASYNC_WriteByteBlocking('l');
                            }
                        } while (keypad_value != '#');
                    }


                 }while(keypad_value != '#');
            
        }
                
   
                        
        
            else
            {
                ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
                ret = lcd_4bit_send_string_pos(&lcd, 1, 1, "Wrong Pass!!");
                ret = lcd_4bit_send_string_pos(&lcd, 2, 1, "Try Again");
                __delay_ms(2000);
                ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
            }
        }
        else if(keypad_value == '#')
        {
            ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
            index = 0;
            ret = lcd_4bit_send_string_pos(&lcd, 1, 1, "Enter Pass: ");
            break;
        }
        else
        {
            /*NOTHING*/
        }
      
    }   

    
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_intialize();
    ret = lcd_4bit_intialize(&lcd);
    ret = keypad_initialize(&keypad);
    ret = EUSART_ASYNC_Init(&uart);
    
}




