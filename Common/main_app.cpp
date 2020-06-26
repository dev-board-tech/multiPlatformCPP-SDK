/*
 * main_app.cpp
 */

#include <main.h>

#include "include/global.h"
#include <api/init.h>
#include <stdio.h>
#include <api/io_handle.h>
#include <api/dev_request.h>


#if (USE_SCREEN_GUI == true)
#include "lib/gfx/window.h"
#include "lib/gfx/PasswordWindowNumeric.h"
#endif

#if (USE_NEW_SCREEN_GUI == true)
#include "lib/gfx/newButton.h"
#include "lib/gfx/newProgressBar.h"
#include "lib/gfx/newCheckBox.h"
#include "lib/gfx/newScrollBar.h"
#include "lib/gfx/newLabel.h"
#endif /*!USE_NEW_SCREEN_GUI*/


#ifdef _USE_HIH613x
#include <device/hih6130.h>
#endif
#ifdef _USE_MPU60x0_9150
#include <device/mpu60x0_9x50.h>
#endif
#ifdef _USE_AK8975
#include <device/ak8975.h>
#endif
#ifdef _USE_BMP180
#include <device/bmp180.h>
#endif
#ifdef _USE_MPL3115A2
#include <device/mpl3115a2.h>
#endif
#ifdef _USE_MPR121
#include <device/mpr121.h>
#endif
#ifdef _USE_L3GD20
#include <device/l3gd20.h>
#endif
#ifdef _USE_BMA250
#include <device/bma250.h>
#endif
#ifdef _USE_LSM9DS1
#include <device/lsm9ds1.h>
#endif
#ifdef _USE_LPS25HB
#include <device/lps25hb.h>
#endif
#ifdef _USE_MCP79410
#include <device/mcp79410.h>
#endif
#ifdef _USE_TCN75A
#include <device/tcn75s.h>
#endif
#ifdef _USE_SSD1331
#include <device/ssd1331.h>
#endif
#ifdef _USE_LCD_FPGA
#include <device/lcd_fpga.h>
#endif
#include <sys/core_init.h>
#include <app/sys/cmd.h>

#include <app/lwip/http_client/http_client.h>

#if (USE_SCREEN_GUI == true)
GI::Screen::Gfx::Window *MainWindow = NULL;
GI::Screen::Gfx::TextBox *SensorResultTextboxGlobal;
#endif
#if (USE_NEW_SCREEN_GUI == true)
GI::Gfx::button *newBtn1 = NULL;
GI::Gfx::progressBar *newProgressBar1 = NULL;
GI::Gfx::progressBar *newProgressBar2 = NULL;
GI::Gfx::progressBar *newProgressBar3 = NULL;
GI::Gfx::checkBox *newCheckBox1 = NULL;
GI::Gfx::scrollBar *newScrollBar1 = NULL;
GI::Gfx::scrollBar *newScrollBar2 = NULL;
GI::Gfx::label *newLabel1 = NULL;
#endif /*!USE_NEW_SCREEN_GUI*/

#if (USE_UART == 1 && USE_TERMINAL == 1)
Cmd *term_cmd;

void cmdCharRecCallback(char data)
{
	term_cmd->parse(data);
}
#endif

void main_app(void)
{
	GI::Sys::Timer timer_touch = GI::Sys::Timer(20);
	GI::Sys::Timer blink_timer = GI::Sys::Timer(100);

	bool led_state = false;

#ifdef _USE_HIH613x
	GI::Sys::Timer hih613timer = GI::Sys::Timer(1000);
#endif
#if defined(_USE_MPU60x0_9150) && defined(_USE_AK8975)
	GI::Sys::Timer mpu60x0_9x50_timer = GI::Sys::Timer(200);
#endif
#ifdef _USE_BMP180
	GI::Sys::Timer bmp180_timer = GI::Sys::Timer(1000);
#endif
#ifdef _USE_MPL3115A2
	GI::Sys::Timer mpl3115_timer = GI::Sys::Timer(1000);
#endif
#ifdef _USE_MPR121
	GI::Sys::Timer mpr121_timer = GI::Sys::Timer(50);
#endif
#ifdef _USE_L3GD20
    GI::Sys::Timer l3gd20_timer = GI::Sys::Timer(50);
#endif
#ifdef _USE_BMA250
    GI::Sys::Timer bma250_timer = GI::Sys::Timer(50);
#endif
#ifdef _USE_LSM9DS1
    GI::Sys::Timer lsm9ds1_timer = GI::Sys::Timer(50);
#endif
#ifdef _USE_LPS25HB
    GI::Sys::Timer lps25hb_timer = GI::Sys::Timer(25);
#endif
#ifdef _USE_MCP79410
    GI::Sys::Timer mcp79410_timer = GI::Sys::Timer(250);
#endif
#ifdef _USE_TCN75A
    GI::Sys::Timer tcn75a_timer = GI::Sys::Timer(1000);
    GI::Sys::Timer tcn75a_timer_ready = GI::Sys::Timer(100);
#endif


#if (USE_SCREEN_GUI == true)
#if (USE_WINDOW == true)
	/*
	 * Create one parent window.
	 */
	MainWindow = new GI::Screen::Gfx::Window(NULL, dev.SCREEN[0]);
	MainWindow->AllowHScroll = false;
	MainWindow->AllowVScroll = false;
	MainWindow->HideHScroll = true;
	MainWindow->HideVScroll = true;
	MainWindow->MaxMinEnabled = true;
	MainWindow->MinimizeButonEnabled = false;
	MainWindow->CloseButonEnabled = false;
	MainWindow->Caption->textAlign = alignLeft;

	/*
	 * Create a picture box.
	 */
	newPictureBox(MainWindow, FlirPictureBox);
	//FlirPictureBox_Global = FlirPictureBox;
	FlirPictureBox->Position.X = 10;
	FlirPictureBox->Position.Y = 10;
	FlirPictureBox->Size.X = 460;
	FlirPictureBox->Size.Y = 160;
	FlirPictureBox->BackgroundColor = 0xFFFFFFFF;

	/*
	 * Create a text box.
	 */
	newTextBox(MainWindow, SensorResultTextbox);
	SensorResultTextboxGlobal = SensorResultTextbox;
	SensorResultTextbox->Position.X = 10;
	SensorResultTextbox->Position.Y = FlirPictureBox->Position.Y + FlirPictureBox->Size.Y + 10;
	SensorResultTextbox->Size.X = 460;
	SensorResultTextbox->Size.Y = 200;
	SensorResultTextbox->Size.ScrollSize = 50;
	SensorResultTextbox->text->setText((char *)"This is a sensor result textbox");

	/*
	 * Create a button.
	 */
	newButton(MainWindow, Buton1);
	Buton1->Position.X = 10;
	Buton1->Position.Y = SensorResultTextbox->Position.Y + SensorResultTextbox->Size.Y + 10;
	Buton1->Size.X = 100;
	Buton1->Size.Y = 50;

	/*
	 * Create a progress bar.
	 */
	newProgressBar(MainWindow, ProgressBar1);
	ProgressBar1->MinimValue  = 0;
	ProgressBar1->MaximValue = 100;
	ProgressBar1->Value = 50;
	ProgressBar1->Position.X = 10;
	ProgressBar1->Position.Y = Buton1->Position.Y + Buton1->Size.Y + 10;
	ProgressBar1->Size.X = 460;
	ProgressBar1->Size.Y = 30;

	/*
	 * Create a check box.
	 */
	newCheckBox(MainWindow, CheckBox1);
	CheckBox1->Position.X = 10;
	CheckBox1->Position.Y = ProgressBar1->Position.Y + ProgressBar1->Size.Y + 10;
	CheckBox1->Size.X = 460;
	CheckBox1->Size.Y = 30;

	/*
	 * Create a list box.
	 */
	newListBox(MainWindow, ListBox);
	ListBox->Position.X = 10;
	ListBox->Position.Y = CheckBox1->Position.Y + CheckBox1->Size.Y + 10;
	ListBox->Size.X = 460;
	ListBox->Size.Y = MainWindow->Internals.pDisplay->LcdTimings->Y - (CheckBox1->Position.Y + CheckBox1->Size.Y + 30);
	ListBox->Size.ScrollSize = 50;
	ListBox->Size.ItemSizeY = 30;
	ListBox->Size.MinScrollBtnSize = 30;
	ListBox->Caption->textAlign = alignLeft;
#else /* USE_WINDOW == false */
#if (USE_NEW_SCREEN_GUI == false)
	/*
	 * No parent window used.
	 */

	/*
	 * Create a picture box.
	 */
	GI::Screen::Gfx::Picturebox *FlirPictureBox = new GI::Screen::Gfx::Picturebox(dev.SCREEN[0]);
	//FlirPictureBox_Global = FlirPictureBox;
	FlirPictureBox->Position.X = 10;
	FlirPictureBox->Position.Y = 10;
	FlirPictureBox->Size.X = 460;
	FlirPictureBox->Size.Y = 160;
	FlirPictureBox->BackgroundColor = 0xFFFFFFFF;

	/*
	 * Create a text box.
	 */
	GI::Screen::Gfx::TextBox *SensorResultTextbox = new GI::Screen::Gfx::TextBox(dev.SCREEN[0]);
	SensorResultTextboxGlobal = SensorResultTextbox;
	SensorResultTextbox->Position.X = 10;
	SensorResultTextbox->Position.Y = FlirPictureBox->Position.Y + FlirPictureBox->Size.Y + 10;
	SensorResultTextbox->Size.X = 460;
	SensorResultTextbox->Size.Y = 200;
	SensorResultTextbox->Size.ScrollSize = 50;
	SensorResultTextbox->text->setText((char *)"This is a sensor result textbox");

	/*
	 * Create a button.
	 */
	GI::Screen::Gfx::Button *Buton1 = new GI::Screen::Gfx::Button(dev.SCREEN[0]);
	Buton1->Position.X = 10;
	Buton1->Position.Y = SensorResultTextbox->Position.Y + SensorResultTextbox->Size.Y + 10;
	Buton1->Size.X = 100;
	Buton1->Size.Y = 50;

	/*
	 * Create a progress bar.
	 */
	GI::Screen::Gfx::ProgressBar *ProgressBar1 = new GI::Screen::Gfx::ProgressBar(dev.SCREEN[0]);
	ProgressBar1->MinimValue  = 0;
	ProgressBar1->MaximValue = 100;
	ProgressBar1->Value = 50;
	ProgressBar1->Position.X = 10;
	ProgressBar1->Position.Y = Buton1->Position.Y + Buton1->Size.Y + 10;
	ProgressBar1->Size.X = 460;
	ProgressBar1->Size.Y = 30;

	/*
	 * Create a check box.
	 */
	GI::Screen::Gfx::CheckBox *CheckBox1 = new GI::Screen::Gfx::CheckBox(dev.SCREEN[0]);
	CheckBox1->Position.X = 10;
	CheckBox1->Position.Y = ProgressBar1->Position.Y + ProgressBar1->Size.Y + 10;
	CheckBox1->Size.X = 460;
	CheckBox1->Size.Y = 30;

	/*
	 * Create a list box.
	 */
	GI::Screen::Gfx::ListBox *ListBox = new GI::Screen::Gfx::ListBox(dev.SCREEN[0]);
	ListBox->Position.X = 10;
	ListBox->Position.Y = CheckBox1->Position.Y + CheckBox1->Size.Y + 10;
	ListBox->Size.X = 460;
	ListBox->Size.Y = dev.SCREEN[0]->LcdTimings->Y - (CheckBox1->Position.Y + CheckBox1->Size.Y + 30);
	ListBox->Size.ScrollSize = 50;
	ListBox->Size.ItemSizeY = 30;
	ListBox->Size.MinScrollBtnSize = 30;
	ListBox->Caption->textAlign = alignLeft;
#else /*USE_NEW_SCREEN_GUI == true*/

	newBtn1 = new GI::Gfx::button();
	newProgressBar1 = new GI::Gfx::progressBar();
	newProgressBar1->setX(120);
	newProgressBar1->setY(10);
	newProgressBar2 = new GI::Gfx::progressBar();
	newProgressBar2->setX(120);
	newProgressBar2->setY(40);
	newProgressBar2->setValue(100);
	newProgressBar3 = new GI::Gfx::progressBar();
	newProgressBar3->setX(120);
	newProgressBar3->setY(70);
	newProgressBar3->setValue(-90);
	newCheckBox1 = new GI::Gfx::checkBox();
	newCheckBox1->setX(120);
	newCheckBox1->setY(100);
	newScrollBar1 = new GI::Gfx::scrollBar();
	newScrollBar1->setX(120);
	newScrollBar1->setY(130);
	newScrollBar2 = new GI::Gfx::scrollBar();
	newScrollBar2->setX(240);
	newScrollBar2->setY(130);
	newScrollBar2->setWidth(27);
	newScrollBar2->setHeight(100);
	newScrollBar2->setOrientation(GI::vertical);
	newLabel1 = new GI::Gfx::label();
	newLabel1->setX(120);
	newLabel1->setY(160);


#endif /*!USE_NEW_SCREEN_GUI*/
#endif
#if (USE_NEW_SCREEN_GUI == false)
	/*
	 * Populate list box with 256 items.
	 */
	u32 cnt = 0;
	char listbox_buff[32];
	char buff_tmp[10];
	for(; cnt < 6; cnt++)
	{
		strcpy((char *)listbox_buff, "Device ID ");
		utoa(cnt + 1, buff_tmp, 10);
		strcat(listbox_buff, buff_tmp);
		ListBox->add(listbox_buff);
	}
#endif /*!USE_NEW_SCREEN_GUI*/

#if(_USE_PASSWORD_PROTECTION == 1)
	newWindowPasswordNumeric(MainWindow, pass, 2, 2);
#endif
#endif/*!(USE_SCREEN_GUI == true)*/
	/*
	 * Put on parent window caption the IP of ETH interface.
	 */
#if (USE_LWIP == 1)
	GI::string ipAddressStr = GI::string();
	GI::string ip_str_buff = GI::string();
	dev.LWIP[0]->getIp(&ip_str_buff);
	//MainWindow->Caption->setTextF("IP:%s\n\r", ip_str_buff.buff);
	ipAddressStr.set((char *)"IP:");
	ipAddressStr.append(ip_str_buff.buff);
	bool old_state_ip_assigned = false;
	//dev._stdout->printF("IP:%s\n\r", ip_str_buff.buff);
#endif

#ifdef _USE_HIH613x
	GI::Device::Sensor::Hih613x hih6130 = GI::Device::Sensor::Hih613x((char *)_USE_HIH613x);
#endif
#ifdef _USE_MPU60x0_9150
	GI::Device::Sensor::Mpu60x0_9x50 mpu60x0_9x50 = GI::Device::Sensor::Mpu60x0_9x50((char *)_USE_MPU60x0_9150, 0);
#endif
#if defined(_USE_AK8975) && defined(_USE_MPU60x0_9150)
	/*
	 * If AK8975 is inside MPU9150 you need to put this after you initialize the MPU device.
	 */
	GI::Device::Sensor::Ak8975 ak8975_0 = GI::Device::Sensor::Ak8975((char *)_USE_AK8975, 0);
#endif
#ifdef _USE_BMP180
	GI::Device::Sensor::Bmp180 bmp180_0 = GI::Device::Sensor::Bmp180((char *)_USE_BMP180, 0);
#endif
#ifdef _USE_MPL3115A2
	GI::Device::Sensor::Mpl3115a2 mpl3115a2 = GI::Device::Sensor::Mpl3115a2((char *)_USE_MPL3115A2);
#endif
#ifdef _USE_MPR121
	GI::Device::Sensor::Mpr121 mpr121_0 = GI::Device::Sensor::Mpr121((char *)_USE_MPR121, (char *)"", 0);
#endif
#ifdef _USE_L3GD20
	GI::Device::Sensor::L3gd20 l3gd20_0 = GI::Device::Sensor::L3gd20((char *)_USE_L3GD20);
#endif
#ifdef _USE_BMA250
	GI::Device::Sensor::Bma250 bma250_0 = GI::Device::Sensor::Bma250((char *)_USE_BMA250);
#endif
#ifdef _USE_LSM9DS1
	GI::Device::Sensor::Lsm9ds1 lsm9ds1_0 = GI::Device::Sensor::Lsm9ds1((char *)_USE_LSM9DS1, 1, 1);
#endif
#ifdef _USE_LPS25HB
	GI::Device::Sensor::Lps25hb lps25hb_0 = GI::Device::Sensor::Lps25hb((char *)_USE_LPS25HB, 1);
#endif
#ifdef _USE_MCP79410
	GI::Device::Rtc::Mcp79410 mcp79410_0 = GI::Device::Rtc::Mcp79410((char *)_USE_MCP79410);
#endif
#ifdef _USE_TCN75A
	GI::Device::Sensor::Tcn75s tcn75a_0 = GI::Device::Sensor::Tcn75s((char *)_USE_TCN75A, 0);
#endif
#ifdef _USE_SSD1331
	GI::Device::Display::Ssd1331 *ssd1331_0 = new GI::Device::Display::Ssd1331(_USE_SSD1331);
#endif
#ifdef _USE_SSD1306
	GI::Device::Display::Ssd1306 *ssd1306_0 = new GI::Device::Display::Ssd1306(_USE_SSD1306);
#endif
#ifdef _USE_LCD_FPGA
	GI::Device::Display::LcdFpga *lcd_fpga_0 = new GI::Device::Display::LcdFpga(_USE_LCD_FPGA);
#endif

#if (USE_UART == 1 && USE_TERMINAL == 1)
	term_cmd = new Cmd((char *)CONSOLE_UART_IN, (char *)CONSOLE_UART_OUT, (char *)CONSOLE_UART_ERR);
	//GI::Dev::Uart *uartDev;
	//GI::Dev::DevRequest::request((char *)CONSOLE_UART_IN, &uartDev);
	//uartDev->charReceive_Callback = cmdCharRecCallback;
#endif
	/*GI::Sys::Clock::changeCoreClk(25000000);
	unsigned long baud = 1200;
	terminal.ctl(GI::IO::IO_CTL_SET_SPEED, &baud);*/

#if (SHOW_SENSORS_RESULT_ON_SCREEN == 0)
	GI::IO terminal = GI::IO((char *)CONSOLE_UART_OUT);
#endif
	//terminal.write((unsigned char *)buffer, bytesread);
	
#if (USE_SCREEN == true && USE_SCREEN_GUI == false && SCREENS_COUNT > 0)
	/* These functions interact directly with registered driver, the GUI library is not used because the display resolution is too tinny. */
	dev.SCREEN[0]->drawPixel(3, 1, Color::White);
	dev.SCREEN[0]->drawRectangle(1, 3, 5, 5, true, Color::White);
	dev.SCREEN[0]->drawRectangle(1, 9, 5, 5, false, Color::White);
	dev.SCREEN[0]->drawHLine(1, 16, 16, 1, Color::White);//Optimized linear horizontal line.
	dev.SCREEN[0]->drawVLine(18, 10, 8, 1, Color::White);//Optimized linear verical line.
	dev.SCREEN[0]->drawString((char *)"Morgoth CppSDK example application", 16, 0, NULL, true, 0, Color::White);
	dev.SCREEN[0]->drawCircle(32, 23, 8, 1, Color::White);
	dev.SCREEN[0]->drawCircle(50, 23, 8, 0, Color::White);
#ifndef SmartRf06// The TI CC1310 compiler has an issue with floating point operations that make the uC to generate a fault interrupt, I think that is a stack problem.
	dev.SCREEN[0]->drawElipse(69, 23, 8, 4, 1, Color::White);
	dev.SCREEN[0]->drawElipse(83, 23, 4, 8, 0, Color::White);
#endif
	dev.SCREEN[0]->drawLine(90, 16, 110, 25, 1, Color::White);//Complex inclined line.
	dev.SCREEN[0]->drawLine(98, 16, 118, 25, 3, Color::White);//Complex inclined line.
	dev.SCREEN[0]->refresh();
#endif
#ifdef _USE_SSD1331
	if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
	{
	    ssd1331_0->clear(Color::Black);
	    ssd1331_0->drawPixel(3, 1, Color::Red);
	    ssd1331_0->drawRectangle(1, 3, 5, 5, true, Color::Blue);
	    ssd1331_0->drawRectangle(1, 9, 5, 5, false, Color::Red);
	    ssd1331_0->drawHLine(1, 16, 16, 1, Color::Blue);//Optimized linear horizontal line.
	    ssd1331_0->drawVLine(18, 10, 8, 1, Color::Red);//Optimized linear verical line.
	    ssd1331_0->drawString((char *)"Morgoth CppSDK example application", 16, 0, NULL, true, Color::Black, Color::Green);
	    ssd1331_0->drawCircle(32, 23, 8, 1, Color::Blue);
	    ssd1331_0->drawCircle(50, 23, 8, 0, Color::Red);
#ifndef SmartRf06// The TI CC1310 compiler has an issue with floating point operations that make the uC to generate a fault interrupt, I think that is a stack problem.
	    ssd1331_0->drawElipse(69, 23, 8, 4, 1, Color::Yellow);
	    ssd1331_0->drawElipse(83, 23, 4, 8, 0, Color::Red);
#endif
	    ssd1331_0->drawLine(90, 16, 110, 25, 1, Color::YellowGreen);//Complex inclined line.
	    ssd1331_0->drawLine(98, 16, 118, 25, 3, Color::Red);//Complex inclined line.
		ssd1331_0->refresh();
		GI::Sys::Timer::delay(2000);
	    ssd1331_0->clear(Color::Black);
		ssd1331_0->refresh();
	}
#endif
#ifdef _USE_SSD1306
	if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
	{
		ssd1306_0->clear(Color::Black);
		ssd1306_0->drawPixel(3, 1, Color::White);
		ssd1306_0->drawRectangle(1, 3, 5, 5, true, Color::White);
		ssd1306_0->drawRectangle(1, 9, 5, 5, false, Color::White);
		ssd1306_0->drawHLine(1, 16, 16, 1, Color::White);//Optimized linear horizontal line.
		ssd1306_0->drawVLine(18, 10, 8, 1, Color::White);//Optimized linear verical line.
		ssd1306_0->drawString((char *)"Morgoth CppSDK example application", 16, 0, NULL, true, Color::Black, Color::White);
		ssd1306_0->drawCircle(32, 23, 8, 1, Color::White);
		ssd1306_0->drawCircle(50, 23, 8, 0, Color::White);
#ifndef SmartRf06// The TI CC1310 compiler has an issue with floating point operations that make the uC to generate a fault interrupt, I think that is a stack problem.
		ssd1306_0->drawElipse(69, 23, 8, 4, 1, Color::White);
		ssd1306_0->drawElipse(83, 23, 4, 8, 0, Color::White);
#endif
		ssd1306_0->drawLine(90, 16, 110, 25, 1, Color::White);//Complex inclined line.
		ssd1306_0->drawLine(98, 16, 118, 25, 3, Color::White);//Complex inclined line.
		ssd1306_0->refresh();
		GI::Sys::Timer::delay(2000);
	    ssd1306_0->clear(Color::Black);
	    ssd1306_0->refresh();
	}
#endif
#ifdef _USE_LCD_FPGA
if(lcd_fpga_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
{
		lcd_fpga_0->clear(Color::Black);
		lcd_fpga_0->drawPixel(3, 1, Color::White);
		lcd_fpga_0->drawRectangle(1, 3, 5, 5, true, Color::White);
		lcd_fpga_0->drawRectangle(1, 9, 5, 5, false, Color::White);
		lcd_fpga_0->drawHLine(1, 16, 16, 1, Color::White);//Optimized linear horizontal line.
		lcd_fpga_0->drawVLine(18, 10, 8, 1, Color::White);//Optimized linear verical line.
		lcd_fpga_0->drawString((char *)"Morgoth CppSDK example application", 16, 0, NULL, true, Color::Black, Color::White);
		lcd_fpga_0->drawCircle(32, 23, 8, 1, Color::White);
		lcd_fpga_0->drawCircle(50, 23, 8, 0, Color::White);
#ifndef SmartRf06// The TI CC1310 compiler has an issue with floating point operations that make the uC to generate a fault interrupt, I think that is a stack problem.
		lcd_fpga_0->drawElipse(69, 23, 8, 4, 1, Color::White);
		lcd_fpga_0->drawElipse(83, 23, 4, 8, 0, Color::White);
#endif
		lcd_fpga_0->drawLine(90, 16, 110, 25, 1, Color::White);//Complex inclined line.
		lcd_fpga_0->drawLine(98, 16, 118, 25, 3, Color::White);//Complex inclined line.
		lcd_fpga_0->refresh();
		GI::Sys::Timer::delay(5000);
		lcd_fpga_0->clear(Color::Black);
}
#endif
	bool state_hbtn_0 = false;
	bool state_hbtn_0_old = true;
	while(1)
	{
		//GI::Sys::Clock::sleep();
		dev.idle();
#if (USE_UART == 1 && USE_TERMINAL == 1)
		term_cmd->idle();
#endif
#if (USE_LWIP == 1)
		if(old_state_ip_assigned == false && dev.LWIP[0]->ipAssigned == true)
		{
			old_state_ip_assigned = true;
			/*
			 * Update on parent window caption the IP of ETH interface if is assigned by DHCP.
			 */
			GI::string ip_str_buff = GI::string();
			dev.LWIP[0]->getIp(&ip_str_buff);
			//MainWindow->Caption->setTextF("IP:%s\n\r", ip_str_buff.buff);
			//dev._stdout->printF("IP:%s\n\r", ip_str_buff.buff);
			ipAddressStr.set((char *)"IP:");
			ipAddressStr.append(ip_str_buff.buff);
		}
#endif
#if (USE_LWIP == 1)
		if(ipAddressStr.modifyed || dev.SNTP_CLIENT->time_update)
		{
			ipAddressStr.modifyed = 0;
			dev.SNTP_CLIENT->time_update = 0;
			MainWindow->Caption->setTextF(&ipAddressStr);
			/*@todo: "The server does not respond"*/
			//tcp_setup((char *)"google.com",(char *)"GET /");
			if(dev.SNTP_CLIENT->time_str->length)
				MainWindow->Caption->appendF(",Time:%s", dev.SNTP_CLIENT->time_str->buff);
		}
#endif
		/*
		 * Call every 20ms the idle function of touch screen interface
		 * 	and idle function of parent window.
		 */
		if(timer_touch.tick())
		{
#if (USE_SCREEN_GUI == true)
#if (USE_WINDOW == true)
#ifdef USED_TOUCHSCREEN_1
			MainWindow->idle(dev.CURSORCTRL[0]->idle());
#else
			MainWindow->idle(NULL);
#endif
#else /* USE_WINDOW != true */
#ifdef USED_TOUCHSCREEN_1 /* If you don't use a parent window you need to check by your self if a cursor was down inside an item to not be propagated to other items in same location. */
			tControlCommandData *tmpTouch = dev.CURSORCTRL[0]->idle();
#if (USE_NEW_SCREEN_GUI == true)
			newBtn1->mouseEventCapture(tmpTouch);
			newBtn1->idle();
			newProgressBar1->mouseEventCapture(tmpTouch);
			newProgressBar1->idle();
			newProgressBar2->mouseEventCapture(tmpTouch);
			newProgressBar2->idle();
			newProgressBar3->mouseEventCapture(tmpTouch);
			newProgressBar3->idle();
			newCheckBox1->mouseEventCapture(tmpTouch);
			newCheckBox1->idle();
			newScrollBar1->mouseEventCapture(tmpTouch);
			newScrollBar1->idle();
			newScrollBar2->mouseEventCapture(tmpTouch);
			newScrollBar2->idle();
			newLabel1->idle();
#else
			FlirPictureBox->idle(tmpTouch);
			if(FlirPictureBox->Internals.CursorDownInsideBox)
				goto _continue;
			SensorResultTextbox->idle(tmpTouch);
			if(SensorResultTextbox->Internals.CursorDownInsideBox)
				goto _continue;
			Buton1->idle(tmpTouch);
			if(Buton1->Internals.CursorDownInsideBox)
				goto _continue;
			ProgressBar1->idle(tmpTouch);
			if(ProgressBar1->Internals.CursorDownInsideBox)
				goto _continue;
			CheckBox1->idle(tmpTouch);
			if(CheckBox1->Internals.CursorDownInsideBox)
				goto _continue;
			ListBox->idle(tmpTouch);
			if(ListBox->Internals.CursorDownInsideBox)
				goto _continue;
#endif /*!USE_NEW_SCREEN_GUI*/
#else /* !USED_TOUCHSCREEN_1 */ /* For future development (Keyboard selection) */
			FlirPictureBox->idle();
			if(FlirPictureBox->Internals.CursorDownInsideBox)
				goto _continue;
			SensorResultTextbox->idle();
			if(SensorResultTextbox->Internals.CursorDownInsideBox)
				goto _continue;
			Buton1->idle();
			if(Buton1->Internals.CursorDownInsideBox)
				goto _continue;
			ProgressBar1->idle();
			if(ProgressBar1->Internals.CursorDownInsideBox)
				goto _continue;
			CheckBox1->idle();
			if(CheckBox1->Internals.CursorDownInsideBox)
				goto _continue;
			ListBox->idle();
			if(ListBox->Internals.CursorDownInsideBox)
				goto _continue;
#endif
#endif
#endif
#if (_USE_PASSWORD_PROTECTION == 1)
			if(pass->idle())
			{
				if(pass->password->equal((char *)"1234"))
					pass->internals.windowHandler->Visible = false;
				else
				{
					pass->clearText->set((char *)"Wrong password!");
				}
			}
#endif
		}
//#if (USE_SCREEN_GUI == true && USE_SCREEN_GUI == false)
_continue:
//#endif
		if(blink_timer.tick())
		{
			bool state;
			GI::IO::read((char *)"led-0", &state);
			if(state)
			{
				if(led_state)
				{
					blink_timer.interval(780);
					led_state = false;
				}
				else
				{
					blink_timer.interval(180);
					led_state = true;
				}
				GI::IO::write((char *)"led-0", false);
#ifdef _USE_SSD1331
				ssd1331_0->drawRectangle(1, 32, 5, 5, true, Color::Black);
				ssd1331_0->refresh();
#endif
#ifdef _USE_SSD1306
				ssd1306_0->drawRectangle(96, 24, 5, 5, true, Color::Black);
				ssd1306_0->refresh();
#endif
#if (USE_SCREEN == true && USE_SCREEN_GUI == false && SCREENS_COUNT > 0)
				dev.SCREEN[0]->drawRectangle(96, 24, 5, 5, true, Color::Black);
#endif
			}
			else
			{
				blink_timer.interval(20);
				GI::IO::write((char *)"led-0", true);
#ifdef _USE_SSD1331
				ssd1331_0->drawRectangle(1, 32, 5, 5, true, Color::Red);
				ssd1331_0->refresh();
#endif
#ifdef _USE_SSD1306
				ssd1306_0->drawRectangle(96, 24, 5, 5, true, Color::White);
				ssd1306_0->refresh();
#endif
#if (USE_SCREEN == true && USE_SCREEN_GUI == false && SCREENS_COUNT > 0)
				dev.SCREEN[0]->drawRectangle(96, 24, 5, 5, true, Color::White);
#endif
			}
		}
#if defined (__Xmega_FPGA__) || defined (RiscV_FPGA)
		GI::IO::read((char *)"hbtn-0", &state_hbtn_0);
#endif
#ifdef _USE_HIH613x
		if(hih613timer.tick())
		{
			unsigned char hih613x_status = 0;;
			float hih613x_hum = 0;
			float hih613x_temp = 0;
			if(!hih6130.get(&hih613x_status, &hih613x_hum, &hih613x_temp))
			{
				switch(hih613x_status)
				{
				case 0:
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
					ListBox->Items[0]->Caption->setTextF((char *)"HIH613x: T = %3.2f, H = %2.1f", hih613x_temp, hih613x_hum);
#else
					GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"HIH613x: T = %3.2f, H = %2.1f\r", hih613x_temp, hih613x_hum);
#endif
#ifdef _USE_SSD1306
					if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
					{
					}
#endif
#ifdef _USE_SSD1331
					if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
					{
					}
#endif
					break;
				case 1:
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
					ListBox->Items[0]->Caption->setText((char *)"HIH613x: stale data");
#else
					GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"HIH613x: stale data\r");
#endif
#ifdef _USE_SSD1306
					if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
					{
					}
#endif
#ifdef _USE_SSD1331
					if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
					{
					}
#endif
					break;
				case 2:
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
					ListBox->Items[0]->Caption->setText((char *)"HIH613x: in command mode");
#else
					GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"HIH613x: in command mode\r");
#endif
#ifdef _USE_SSD1306
					if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
					{
					}
#endif
#ifdef _USE_SSD1331
					if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
					{
					}
#endif
					break;
				case 3:
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
					ListBox->Items[0]->Caption->setText((char *)"HIH613x: diagnostic");
#else
					GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"HIH613x: diagnostic\r");
#endif
#ifdef _USE_SSD1306
					if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
					{
					}
#endif
#ifdef _USE_SSD1331
					if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
					{
					}
#endif
					break;
				}
			}
			else
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				SensorResultTextbox->text->append((char *)"HIH613x:  error reading temperature and humidity");
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"HIH613x:  error reading temperature and humidity\r");
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
		}
#endif
#ifdef _USE_MPU60x0_9150
		bool mpu60x0_9x50_timer_ticked = false;
		if(mpu60x0_9x50_timer.tick())
		{
			mpu60x0_9x50_timer_ticked = true;
			float mpu60x0_9150_temp = 0.0;
			signed short mpu60x0_9150_gyro_Xg = 0;
			signed short mpu60x0_9150_gyro_Yg = 0;
			signed short mpu60x0_9150_gyro_Zg = 0;
			signed short mpu60x0_9150_accel_Xa = 0;
			signed short mpu60x0_9150_accel_Ya = 0;
			signed short mpu60x0_9150_accel_Za = 0;
			if(!mpu60x0_9x50.getTempData(&mpu60x0_9150_temp))
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[1]->Caption->setTextF((char *)"MPU60x0: Temp:  %3.2f Gr Celsius", mpu60x0_9150_temp);
#else
				GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"MPU60x0: Temp:  %3.2f Gr Celsius\r", mpu60x0_9150_temp);
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
			else
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[1]->Caption->setText((char *)"MPU60x0: error reading temperature");
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"MPU60x0: error reading temperature\r");
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
			if(!mpu60x0_9x50.getGyroData(&mpu60x0_9150_gyro_Xg, &mpu60x0_9150_gyro_Yg, &mpu60x0_9150_gyro_Zg))
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[2]->Caption->setTextF((char *)"MPU60x0: Giro:  Xg = %6d, Yg = %6d, Zg = %6d", mpu60x0_9150_gyro_Xg, mpu60x0_9150_gyro_Yg, mpu60x0_9150_gyro_Zg);
#else
				GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"MPU60x0: Giro:  Xg = %6d, Yg = %6d, Zg = %6d\r", mpu60x0_9150_gyro_Xg, mpu60x0_9150_gyro_Yg, mpu60x0_9150_gyro_Zg);
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
			else
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[2]->Caption->setText((char *)"MPU60x0: error reading giroscope");
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"MPU60x0: error reading giroscope\r");
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
			if(!mpu60x0_9x50.getAccelData(&mpu60x0_9150_accel_Xa, &mpu60x0_9150_accel_Ya, &mpu60x0_9150_accel_Za))
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[3]->Caption->setTextF((char *)"MPU60x0: Accel: Xa = %6d, Ya = %6d, Za = %6d", mpu60x0_9150_accel_Xa, mpu60x0_9150_accel_Ya, mpu60x0_9150_accel_Za);
#else
				GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"MPU60x0: Accel: Xa = %6d, Ya = %6d, Za = %6d\r", mpu60x0_9150_accel_Xa, mpu60x0_9150_accel_Ya, mpu60x0_9150_accel_Za);
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
			else
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[3]->Caption->setText((char *)"MPU60x0: error reading accelerometer");
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"MPU60x0: error reading accelerometer\r");
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
		}
#endif
#if defined(_USE_AK8975) && defined(_USE_MPU60x0_9150)
		if(mpu60x0_9x50_timer_ticked)
		{
			signed short AK8975_X_Axis = 0, AK8975_Y_Axis = 0, AK8975_Z_Axis = 0;
			if(!ak8975_0.getMag(&AK8975_X_Axis, &AK8975_Y_Axis, &AK8975_Z_Axis))
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[4]->Caption->setTextF((char *)"AK8975: Magne: Xm = %6d, Ym = %6d, Zm = %6d", AK8975_X_Axis, AK8975_Y_Axis, AK8975_Z_Axis);
#else
				GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"AK8975: Magne: Xm = %6d, Ym = %6d, Zm = %6d\r", AK8975_X_Axis, AK8975_Y_Axis, AK8975_Z_Axis);
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
			else
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[4]->Caption->setText((char *)"AK8975: error reading magnetometer");
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"AK8975: error reading magnetometer\r");
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
		}
#endif
#ifdef _USE_BMP180
		if(bmp180_timer.tick())
		{
			float bmp180_temperature = 0.0;
			float bmp180_pressure = 0.0;
			float bmp180_altitude = 0.0;
			if(!bmp180_0.getTemp(&bmp180_temperature) &&
					!bmp180_0.getPressure(&bmp180_pressure, GI::Device::Sensor::Bmp180::BMP180_CTRL_MEAS_OSS_8) &&
						!bmp180_0.getAltitude(&bmp180_altitude, GI::Device::Sensor::Bmp180::BMP180_CTRL_MEAS_OSS_8))
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[5]->Caption->setTextF((char *)"BMP180: Temp = %3.1f, Press = %4.2f, Alt = %4.2f", bmp180_temperature, bmp180_pressure, bmp180_altitude);
#else
				GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"BMP180: Temp = %3.1f, Press = %4.2f, Alt = %4.2f\r", bmp180_temperature, bmp180_pressure, bmp180_altitude);
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
			else
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[5]->Caption->setText((char *)"BMP180: error reading temp, press and altitude");
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"BMP180: error reading temp, press and altitude\r");
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
		}
#endif
#ifdef _USE_MPL3115A2
		if(mpl3115_timer.tick())
		{
			float mpl3115a2_pressure = 0.0, mpl3115a2_altitude = 0.0, mpl3115a2_temp = 0.0;
			if(!mpl3115a2.getAltTemp(2, &mpl3115a2_pressure, &mpl3115a2_altitude, &mpl3115a2_temp))
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[6]->Caption->setTextF((char *)"MPL3115A1: T = %3.3f, P = %3.5f, Alt = %4.3f", mpl3115a2_temp, 0.0, mpl3115a2_altitude);
#else
				GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"MPL3115A1: T = %3.3f, P = %3.5f, Alt = %4.3f\r", mpl3115a2_temp, 0.0, mpl3115a2_altitude);
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
			else
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[6]->Caption->setText((char *)"MPL3115A1: error reading temp, press and altitude");
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"MPL3115A1: error reading temp, press and altitude\r");
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
		}
#endif
#ifdef _USE_MPR121
		if(mpr121_timer.tick())
		{
			mpr121_ret_t mpr121_return;
			if(!mpr121_0.idle(&mpr121_return))
			{
				if(mpr121_return.pushed)
				{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
					ListBox->Items[7]->Caption->setTextF((char *)"MPR121: Pushed   - K0=%u, K1=%u, K2=%u, K3=%u, K4=%u, K5=%u, K6=%u, K7=%u, K8=%u, K9=%u, K10=%u, K11=%u",     (unsigned long)mpr121_return.pushed & 0x01,   (unsigned long)(mpr121_return.pushed >> 1) & 0x01,   (unsigned long)(mpr121_return.pushed >> 2) & 0x01,   (unsigned long)(mpr121_return.pushed >> 3) & 0x01,   (unsigned long)(mpr121_return.pushed >> 4) & 0x01,   (unsigned long)(mpr121_return.pushed >> 5) & 0x01,   (unsigned long)(mpr121_return.pushed >> 6) & 0x01,   (unsigned long)(mpr121_return.pushed >> 7) & 0x01,   (unsigned long)(mpr121_return.pushed >> 8) & 0x01,   (unsigned long)(mpr121_return.pushed >> 9) & 0x01,   (unsigned long)(mpr121_return.pushed >> 10) & 0x01,   (unsigned long)(mpr121_return.pushed >> 11) & 0x01);
#else
					GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"MPR121: Pushed   - K0=%u, K1=%u, K2=%u, K3=%u, K4=%u, K5=%u, K6=%u, K7=%u, K8=%u, K9=%u, K10=%u, K11=%u\r",     (unsigned long)mpr121_return.pushed & 0x01,   (unsigned long)(mpr121_return.pushed >> 1) & 0x01,   (unsigned long)(mpr121_return.pushed >> 2) & 0x01,   (unsigned long)(mpr121_return.pushed >> 3) & 0x01,   (unsigned long)(mpr121_return.pushed >> 4) & 0x01,   (unsigned long)(mpr121_return.pushed >> 5) & 0x01,   (unsigned long)(mpr121_return.pushed >> 6) & 0x01,   (unsigned long)(mpr121_return.pushed >> 7) & 0x01,   (unsigned long)(mpr121_return.pushed >> 8) & 0x01,   (unsigned long)(mpr121_return.pushed >> 9) & 0x01,   (unsigned long)(mpr121_return.pushed >> 10) & 0x01,   (unsigned long)(mpr121_return.pushed >> 11) & 0x01);
#endif
#ifdef _USE_SSD1306
					if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
					{
					}
#endif
#ifdef _USE_SSD1331
					if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
					{
					}
#endif
				}
				if(mpr121_return.released)
				{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
					ListBox->Items[7]->Caption->setTextF((char *)"MPR121: Released - K0=%u, K1=%u, K2=%u, K3=%u, K4=%u, K5=%u, K6=%u, K7=%u, K8=%u, K9=%u, K10=%u, K11=%u", (unsigned long)mpr121_return.released & 0x01, (unsigned long)(mpr121_return.released >> 1) & 0x01, (unsigned long)(mpr121_return.released >> 2) & 0x01, (unsigned long)(mpr121_return.released >> 3) & 0x01, (unsigned long)(mpr121_return.released >> 4) & 0x01, (unsigned long)(mpr121_return.released >> 5) & 0x01, (unsigned long)(mpr121_return.released >> 6) & 0x01, (unsigned long)(mpr121_return.released >> 7) & 0x01, (unsigned long)(mpr121_return.released >> 8) & 0x01, (unsigned long)(mpr121_return.released >> 9) & 0x01, (unsigned long)(mpr121_return.released >> 10) & 0x01, (unsigned long)(mpr121_return.released >> 11) & 0x01);
#else
					GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"MPR121: Released - K0=%u, K1=%u, K2=%u, K3=%u, K4=%u, K5=%u, K6=%u, K7=%u, K8=%u, K9=%u, K10=%u, K11=%u\r", (unsigned long)mpr121_return.released & 0x01, (unsigned long)(mpr121_return.released >> 1) & 0x01, (unsigned long)(mpr121_return.released >> 2) & 0x01, (unsigned long)(mpr121_return.released >> 3) & 0x01, (unsigned long)(mpr121_return.released >> 4) & 0x01, (unsigned long)(mpr121_return.released >> 5) & 0x01, (unsigned long)(mpr121_return.released >> 6) & 0x01, (unsigned long)(mpr121_return.released >> 7) & 0x01, (unsigned long)(mpr121_return.released >> 8) & 0x01, (unsigned long)(mpr121_return.released >> 9) & 0x01, (unsigned long)(mpr121_return.released >> 10) & 0x01, (unsigned long)(mpr121_return.released >> 11) & 0x01);
#endif
#ifdef _USE_SSD1306
					if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
					{
					}
#endif
#ifdef _USE_SSD1331
					if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
					{
					}
#endif
				}
			}
		}
#endif
#ifdef _USE_L3GD20
		if(l3gd20_timer.tick())
		{
			float l3gd20_Xg = 0;
			float l3gd20_Yg = 0;
			float l3gd20_Zg = 0;
			if(!l3gd20_0.read(&l3gd20_Xg, &l3gd20_Yg, &l3gd20_Zg))
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[8]->Caption->setTextF((char *)"L3GD20: Giro:  Xg = %6.4f, Yg = %6.4f, Zg = %6.4f", l3gd20_Xg, l3gd20_Yg, l3gd20_Zg);
#else
				GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"L3GD20: Giro:  Xg = %6.4f, Yg = %6.4f, Zg = %6.4f\r", l3gd20_Xg, l3gd20_Yg, l3gd20_Zg);
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
			else
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[8]->Caption->setText((char *)"L3GD20: error reading giroscope");
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"L3GD20: error reading giroscope\r");
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
		}
#endif
#ifdef _USE_BMA250
		if(bma250_timer.tick())
		{
			signed short bma250_Xg = 0;
			signed short bma250_Yg = 0;
			signed short bma250_Zg = 0;
			if(!bma250_0.read(&bma250_Xg, &bma250_Yg, &bma250_Zg))
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[9]->Caption->setTextF((char *)"BMA250: Accel:  Xa = %6d, Ya = %6d, Za = %6d", bma250_Xg, bma250_Yg, bma250_Zg);
#else
				GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"BMA250: Accel:  Xa = %6d, Ya = %6d, Za = %6d\r", bma250_Xg, bma250_Yg, bma250_Zg);
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
			else
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[9]->Caption->setText((char *)"BMA250: error reading accelerometer");
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"BMA250: error reading accelerometer\r");
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
			float bma250_temp = 0.0;
			if(!bma250_0.read(&bma250_temp))
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[10]->Caption->setTextF((char *)"BMA250: Temp:  %3.2f Gr Celsius", bma250_temp);
#else
				GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"BMA250: Temp:  %3.2f Gr Celsius\r", bma250_temp);
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
			else
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[10]->Caption->setText((char *)"BMA250: error reading temperature");
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"BMA250: error reading temperature\r");
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
		}
#endif
#ifdef _USE_LSM9DS1
		if(lsm9ds1_timer.tick()
#if defined (__Xmega_FPGA__) || defined (RiscV_FPGA)
		&& state_hbtn_0 == false
#endif
		)
		{
#if defined (__Xmega_FPGA__) || defined (RiscV_FPGA)
			if(state_hbtn_0_old != state_hbtn_0)
			{
				state_hbtn_0_old = state_hbtn_0;
				if(dev.SCREEN[0])
					dev.SCREEN[0]->clear(Color::Black);
			}
#endif
#ifdef _USE_SSD1306
			ssd1306_0->clear(Color::Black);
#endif
			float lsm9ds1_Temp = 0.0;
			if(!lsm9ds1_0.readTemp(&lsm9ds1_Temp))
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
#if (USE_NEW_SCREEN_GUI == false)
				ListBox->Items[0]->Caption->setTextF((char *)"LSM9DS1: Temp:  %3.2f Gr Celsius", lsm9ds1_Temp);
#endif /*!USE_NEW_SCREEN_GUI*/
#else
				GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"LSM9DS1: Temp:  %3.2f Gr Celsius\r", lsm9ds1_Temp);
#endif
#if (USE_SCREEN == true && USE_SCREEN_GUI == false && SCREENS_COUNT > 0)
				if(dev.SCREEN[0])/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					unsigned char gr = (unsigned char)lsm9ds1_Temp;
					unsigned char gr_dec = (lsm9ds1_Temp - (float)gr) * 100.0;
					GI::string tmpString = GI::string((char *)" %3d.%2d Gr Celsius", gr, gr_dec);
					dev.SCREEN[0]->drawRectangle(0, 0, 128, 8, true, Color::Black);
					dev.SCREEN[0]->drawString(tmpString.buff, 0, 0, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					unsigned char gr = (unsigned char)lsm9ds1_Temp;
					unsigned char gr_dec = (lsm9ds1_Temp - (float)gr) * 100.0;
					GI::string tmpString = GI::string((char *)" %3d.%2d Gr Celsius", gr, gr_dec);
					ssd1306_0->drawString(tmpString.buff, 0, 0, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					GI::string tmpString = GI::string((char *)"LSM9DS1: Temp:  %3.2f Gr Celsius", lsm9ds1_Temp);
					ssd1331_0->drawString(tmpString.buff, 0, 0, NULL, false, Color::Black, Color::White);
				}
#endif
			}
			else
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
#if (USE_NEW_SCREEN_GUI == false)
				ListBox->Items[0]->Caption->setText((char *)"LSM9DS1: error reading temperature");
#endif /*!USE_NEW_SCREEN_GUI*/
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"LSM9DS1: error reading temperature\r");
#endif
#if (USE_SCREEN == true && USE_SCREEN_GUI == false && SCREENS_COUNT > 0)
				if(dev.SCREEN[0])/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					dev.SCREEN[0]->drawRectangle(0, 0, 128, 8, true, Color::Black);
					dev.SCREEN[0]->drawString((char *)"LSM9DS1: error reading temperature", 0, 0, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					ssd1306_0->drawString((char *)"LSM9DS1: error reading temperature", 0, 0, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					ssd1331_0->drawString((char *)"LSM9DS1: error reading temperature", 0, 0, NULL, false, Color::Black, Color::White);
				}
#endif
			}
			signed short lsm9ds1_Xa = 0;
			signed short lsm9ds1_Ya = 0;
			signed short lsm9ds1_Za = 0;
			if(!lsm9ds1_0.readAccel(&lsm9ds1_Xa, &lsm9ds1_Ya, &lsm9ds1_Za))
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
#if (USE_NEW_SCREEN_GUI == false)
				ListBox->Items[1]->Caption->setTextF((char *)"LSM9DS1: Accel:  Xa = %6d, Ya = %6d, Za = %6d", lsm9ds1_Xa, lsm9ds1_Ya, lsm9ds1_Za);
#endif /*!USE_NEW_SCREEN_GUI*/
#else
				GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"LSM9DS1: Accel:  Xa = %6d, Ya = %6d, Za = %6d\r", lsm9ds1_Xa, lsm9ds1_Ya, lsm9ds1_Za);
#endif
#if (USE_SCREEN == true && USE_SCREEN_GUI == false && SCREENS_COUNT > 0)
				if(dev.SCREEN[0])/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					GI::string tmpString = GI::string((char *)" XYZa=%6d,%6d,%6d", lsm9ds1_Xa, lsm9ds1_Ya, lsm9ds1_Za);
					dev.SCREEN[0]->drawRectangle(0, 8, 128, 8, true, Color::Black);
					dev.SCREEN[0]->drawString(tmpString.buff, 0, 8, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					GI::string tmpString = GI::string((char *)" XYZa=%6d,%6d,%6d", lsm9ds1_Xa, lsm9ds1_Ya, lsm9ds1_Za);
					ssd1306_0->drawString(tmpString.buff, 0, 8, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					GI::string tmpString = GI::string((char *)"LSM9DS1: Accel:  Xa = %6d, Ya = %6d, Za = %6d", lsm9ds1_Xa, lsm9ds1_Ya, lsm9ds1_Za);
					ssd1331_0->drawString(tmpString.buff, 0, 8, NULL, false, Color::Black, Color::White);
				}
#endif
			}
			else
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
#if (USE_NEW_SCREEN_GUI == false)
				ListBox->Items[1]->Caption->setText((char *)"LSM9DS1: error reading accelerometer");
#endif /*!USE_NEW_SCREEN_GUI*/
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"LSM9DS1: error reading accelerometer\r");
#endif
#if (USE_SCREEN == true && USE_SCREEN_GUI == false && SCREENS_COUNT > 0)
				if(dev.SCREEN[0])/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					dev.SCREEN[0]->drawRectangle(0, 8, 128, 8, true, Color::Black);
					dev.SCREEN[0]->drawString((char *)"LSM9DS1: error reading accelerometer", 0, 8, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					ssd1306_0->drawString((char *)"LSM9DS1: error reading accelerometer", 0, 8, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					ssd1331_0->drawString((char *)"LSM9DS1: error reading accelerometer", 0, 8, NULL, false, Color::Black, Color::White);
				}
#endif
			}
			signed short lsm9ds1_Xg = 0;
			signed short lsm9ds1_Yg = 0;
			signed short lsm9ds1_Zg = 0;
			if(!lsm9ds1_0.readGyro(&lsm9ds1_Xg, &lsm9ds1_Yg, &lsm9ds1_Zg))
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
#if (USE_NEW_SCREEN_GUI == false)
				ListBox->Items[2]->Caption->setTextF((char *)"LSM9DS1: Gyro:  Xg = %6d, Yg = %6d, Zg = %6d", lsm9ds1_Xg, lsm9ds1_Yg, lsm9ds1_Zg);
#endif /*!USE_NEW_SCREEN_GUI*/
#else
				GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"LSM9DS1: Gyro:  Xg = %6d, Yg = %6d, Zg = %6d\r", lsm9ds1_Xg, lsm9ds1_Yg, lsm9ds1_Zg);
#endif
#if (USE_SCREEN == true && USE_SCREEN_GUI == false && SCREENS_COUNT > 0)
				if(dev.SCREEN[0])/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					GI::string tmpString = GI::string((char *)" XYZg=%6d,%6d,%6d", lsm9ds1_Xg, lsm9ds1_Yg, lsm9ds1_Zg);
					dev.SCREEN[0]->drawRectangle(0, 16, 128, 8, true, Color::Black);
					dev.SCREEN[0]->drawString(tmpString.buff, 0, 16, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					GI::string tmpString = GI::string((char *)" XYZg=%6d,%6d,%6d", lsm9ds1_Xg, lsm9ds1_Yg, lsm9ds1_Zg);
					ssd1306_0->drawString(tmpString.buff, 0, 16, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					GI::string tmpString = GI::string((char *)"LSM9DS1: Gyro:  Xg = %6d, Yg = %6d, Zg = %6d", lsm9ds1_Xg, lsm9ds1_Yg, lsm9ds1_Zg);
					ssd1331_0->drawString(tmpString.buff, 0, 16, NULL, false, Color::Black, Color::White);
				}
#endif
			}
			else
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
#if (USE_NEW_SCREEN_GUI == false)
				ListBox->Items[2]->Caption->setText((char *)"LSM9DS1: error reading gyroscope");
#endif /*!USE_NEW_SCREEN_GUI*/
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"LSM9DS1: error reading gyroscope\r");
#endif
#if (USE_SCREEN == true && USE_SCREEN_GUI == false && SCREENS_COUNT > 0)
				if(dev.SCREEN[0])/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					dev.SCREEN[0]->drawRectangle(0, 16, 128, 8, true, Color::Black);
					dev.SCREEN[0]->drawString((char *)"LSM9DS1: error reading gyroscope", 0, 16, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					ssd1306_0->drawString((char *)"LSM9DS1: error reading gyroscope", 0, 16, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					ssd1331_0->drawString((char *)"LSM9DS1: error reading gyroscope", 0, 16, NULL, false, Color::Black, Color::White);
				}
#endif
			}
			signed short lsm9ds1_Xm = 0;
			signed short lsm9ds1_Ym = 0;
			signed short lsm9ds1_Zm = 0;
			if(!lsm9ds1_0.readMag(&lsm9ds1_Xm, &lsm9ds1_Ym, &lsm9ds1_Zm))
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
#if (USE_NEW_SCREEN_GUI == false)
				ListBox->Items[3]->Caption->setTextF((char *)"LSM9DS1: Mag:  Xm = %6d, Ym = %6d, Zm = %6d", lsm9ds1_Xm, lsm9ds1_Ym, lsm9ds1_Zm);
#endif /*!USE_NEW_SCREEN_GUI*/
#else
				GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"LSM9DS1: Mag:  Xm = %6d, Ym = %6d, Zm = %6d\r", lsm9ds1_Xm, lsm9ds1_Ym, lsm9ds1_Zm);
#endif
#if (USE_SCREEN == true && USE_SCREEN_GUI == false && SCREENS_COUNT > 0)
				if(dev.SCREEN[0])/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					GI::string tmpString = GI::string((char *)" XYZm=%6d,%6d,%6d", lsm9ds1_Xm, lsm9ds1_Ym, lsm9ds1_Zm);
					dev.SCREEN[0]->drawRectangle(0, 24, 128, 8, true, Color::Black);
					dev.SCREEN[0]->drawString(tmpString.buff, 0, 24, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					GI::string tmpString = GI::string((char *)" XYZm=%6d,%6d,%6d", lsm9ds1_Xm, lsm9ds1_Ym, lsm9ds1_Zm);
					ssd1306_0->drawString(tmpString.buff, 0, 24, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					GI::string tmpString = GI::string((char *)"LSM9DS1: Mag:  Xm = %6d, Ym = %6d, Zm = %6d", lsm9ds1_Xm, lsm9ds1_Ym, lsm9ds1_Zm);
					ssd1331_0->drawString(tmpString.buff, 0, 24, NULL, false, Color::Black, Color::White);
				}
#endif
			}
			else
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
#if (USE_NEW_SCREEN_GUI == false)
				ListBox->Items[3]->Caption->setText((char *)"LSM9DS1: error reading magnetometer");
#endif /*!USE_NEW_SCREEN_GUI*/
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"LSM9DS1: error reading magnetometer\r");
#endif
#if (USE_SCREEN == true && USE_SCREEN_GUI == false && SCREENS_COUNT > 0)
				if(dev.SCREEN[0])/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					dev.SCREEN[0]->drawRectangle(0, 24, 128, 8, true, Color::Black);
					dev.SCREEN[0]->drawString((char *)"LSM9DS1: error reading magnetometer", 0, 24, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					ssd1306_0->drawString((char *)"LSM9DS1: error reading magnetometer", 0, 24, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					ssd1331_0->drawString((char *)"LSM9DS1: error reading magnetometer", 0, 24, NULL, false, Color::Black, Color::White);
				}
#endif
			}
#ifdef _USE_SSD1306
			ssd1306_0->refresh();
#endif
		}
#endif
#ifdef _USE_LPS25HB
		if(lps25hb_timer.tick()
#if defined (__Xmega_FPGA__) || defined (RiscV_FPGA)
		&& state_hbtn_0 == true
#endif
		)
		{
#if defined (__Xmega_FPGA__) || defined (RiscV_FPGA)
			if(state_hbtn_0_old != state_hbtn_0)
			{
				state_hbtn_0_old = state_hbtn_0;
				if(dev.SCREEN[0])
					dev.SCREEN[0]->clear(Color::Black);
			}
#endif
			float lps25hb_Temp = 0.0;
			if(!lps25hb_0.readTemp(&lps25hb_Temp))
			{
#ifdef _USE_SSD1306
				ssd1306_0->clear(Color::Black);
#endif
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
#if (USE_NEW_SCREEN_GUI == false)
				ListBox->Items[4]->Caption->setTextF((char *)"LPS25HB: Temp:  %3.2f Gr Celsius", lps25hb_Temp);
#endif /*!USE_NEW_SCREEN_GUI*/
#else
				GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"LPS25HB: Temp:  %3.2f Gr Celsius\r", lps25hb_Temp);
#endif
#if defined(_USE_SSD1306) || defined(_USE_SSD1331) || (USE_SCREEN == true && USE_SCREEN_GUI == false && SCREENS_COUNT > 0)
				unsigned char gr = (unsigned char)lps25hb_Temp;
				unsigned char gr_dec = (lps25hb_Temp - (float)gr) * 100.0;
				GI::string tmpString = GI::string((char *)"Temp: %3d.%2d Gr Celsius", gr, gr_dec);
#endif
#if (USE_SCREEN == true && USE_SCREEN_GUI == false && SCREENS_COUNT > 0)
				if(dev.SCREEN[0])/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					dev.SCREEN[0]->drawRectangle(0, 0, 128, 8, true, Color::Black);
					dev.SCREEN[0]->drawString(tmpString.buff, 0, 0, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					ssd1306_0->drawString(tmpString.buff, 0, 0, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					ssd1331_0->drawString(tmpString.buff, 0, 0, NULL, false, Color::Black, Color::White);
				}
#endif
			}
			/*else
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[15]->Caption->setText((char *)"LPS25HB: error reading temperature");
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"LPS25HB: error reading temperature\r");
#endif*/
			float lps25hb_Press = 0.0;
			if(!lps25hb_0.readPress(&lps25hb_Press))
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
#if (USE_NEW_SCREEN_GUI == false)
				ListBox->Items[5]->Caption->setTextF((char *)"LPS25HB: Press:  %4.2f", lps25hb_Press);
#endif /*!USE_NEW_SCREEN_GUI*/
#else
				GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"LPS25HB: Press:  %4.2f\r", lps25hb_Press);
#endif
#if defined(_USE_SSD1306) || defined(_USE_SSD1331) || (USE_SCREEN == true && USE_SCREEN_GUI == false && SCREENS_COUNT > 0)
				unsigned short press = (unsigned short)lps25hb_Press;
				unsigned char press_dec = (lps25hb_Press - (float)press) * 100.0;
				GI::string tmpString = GI::string((char *)"Press: %4d.%2d", press, press_dec);
#endif
#if (USE_SCREEN == true && USE_SCREEN_GUI == false && SCREENS_COUNT > 0)
				if(dev.SCREEN[0])/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					dev.SCREEN[0]->drawRectangle(0, 8, 128, 8, true, Color::Black);
					dev.SCREEN[0]->drawString(tmpString.buff, 0, 8, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					ssd1306_0->drawString(tmpString.buff, 0, 8, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
					ssd1331_0->drawString(tmpString.buff, 0, 8, NULL, false, Color::Black, Color::White);
				}
#endif
#ifdef _USE_SSD1306
				ssd1306_0->refresh();
#endif
			}
			/*else
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[16]->Caption->setText((char *)"LPS25HB: error reading pressure");
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"LPS25HB: error reading pressure\r");
#endif*/
		}
#endif
#ifdef _USE_MCP79410
		if(mcp79410_timer.tick())
		{
			GI::string *time = mcp79410_0.readTime(NULL);
			if(time && time->length)
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[17]->Caption->setTextF((char *)"MCP79410: Time:  %s", time->buff);
#else
				GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"MCP79410: Time:  %s\r", time->buff);
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
			else
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[17]->Caption->setText((char *)"MCP79410: error reading time");
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"MCP79410: error reading time\r");
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
		}
#endif
#ifdef _USE_TCN75A// Non blocking procedure because a temperature conversion will eat from 30 to 240ms
		if(tcn75a_timer.tick())
		{
			if(tcn75a_0.startOneShot())
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[18]->Caption->setText((char *)"TCN75A: error reading temperature");
#else
				GI::IO::write((char *)CONSOLE_UART_OUT, (char *)"TCN75A: error reading temperature\r");
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
		}
		if(tcn75a_timer_ready.tick())
		{
			float tcn75a_Temp = 0.0;
			if(!tcn75a_0.readTemp(&tcn75a_Temp))
			{
#if (SHOW_SENSORS_RESULT_ON_SCREEN == 1)
				ListBox->Items[18]->Caption->setTextF((char *)"TCN75A: Temp:  %3.3f Gr Celsius", tcn75a_Temp);
#else
				GI::IO::writeF((char *)CONSOLE_UART_OUT, (char *)"TCN75A: Temp:  %3.3f Gr Celsius\r", tcn75a_Temp);
#endif
#ifdef _USE_SSD1306
				if(ssd1306_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
#ifdef _USE_SSD1331
				if(ssd1331_0)/* This display driver is used like an external device (non registered display driver), you can declare more displays in this form, even multiplexed on same SPI interface. */
				{
				}
#endif
			}
		}
#endif
	}
}

