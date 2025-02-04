#include "subsystems/LEDSubsystem.h"

static const LEDSubsystem::Color c_defaultColor = LEDSubsystem::CreateColor(255, 255, 255, 10);
static constexpr int c_defaultLEDNum = 8;
static constexpr int c_defaultLEDOffset = 0;

LEDSubsystem::LEDSubsystem()
{
  wpi::log::DataLog& log = frc::DataLogManager::GetLog();
#ifndef THING1
  m_candleConfig.stripType = LEDStripType::RGB; // set the strip type to RGB
  m_candleConfig.brightnessScalar = 1.0; // dim the LEDs to half brightness
  m_candle.ConfigAllSettings(m_candleConfig);
  m_candle.ClearAnimation(0);
  // m_candle.ClearAnimation(1);
  m_candle.SetLEDs(43, 6, 0, 255, c_ledOffset, c_ledNum);
  // int red = c_defaultColor.red;
  // int green = c_defaultColor.green;
  // int blue = c_defaultColor.blue;
  // int white = c_defaultColor.white;
  // m_candle.SetLEDs(red, green, blue, white, c_defaultLEDOffset, c_defaultLEDNum);
  m_speed = c_defaultSpeed;

  m_log = wpi::log::DoubleLogEntry(log, "/subsystem/led");

  /*ctre::phoenix::ErrorCode error =*/ m_candle.GetLastError(); // gets the last error generated by the CANdle

  CANdleFaults faults;
  /*ctre::phoenix::ErrorCode faultsError =*/ m_candle.GetFaults(faults); // fills faults with the current CANdle faults; returns the last error generated
#endif
  // printf("candle error: %d", error);
  // printf("candle fault: %d", faultsError);
}

void LEDSubsystem::Periodic()
{
  // m_log.Append(add_data_here);
}

LEDSubsystem::Color LEDSubsystem::CreateColor(int r, int g, int b, int w)
{
  Color color;
  color.red = r;
  color.green = g;
  color.blue = b;
  color.white = w;
  return color;
}

void LEDSubsystem::SetAnimation(Color rgbw, Animation animate)
{
#ifndef THING1
  int red = rgbw.red;
  int green = rgbw.green;
  int blue = rgbw.blue;
  int white = rgbw.white;
  switch (animate)
  {
    case (Animation::kSolid):
      m_candle.ClearAnimation(0);
      m_candle.SetLEDs(red, green, blue, white, c_ledOffset, c_ledNum);
      break;
    case (Animation::kFade):
    {
      m_singleFadeAnimation.SetR(red);
      m_singleFadeAnimation.SetG(green);
      m_singleFadeAnimation.SetB(blue);
      m_singleFadeAnimation.SetW(white);
      m_candle.Animate(m_singleFadeAnimation);
      break;
    }
    case (Animation::kFlow):
    {
      m_colorFlowAnimation.SetR(red);
      m_colorFlowAnimation.SetG(green);
      m_colorFlowAnimation.SetB(blue);
      m_colorFlowAnimation.SetW(white);
      m_candle.Animate(m_colorFlowAnimation);
      break;
    }
    case (Animation::kStrobe):
    {
      m_strobeAnimation.SetR(red);
      m_strobeAnimation.SetG(green);
      m_strobeAnimation.SetB(blue);
      m_strobeAnimation.SetW(white);
      m_candle.Animate(m_strobeAnimation);
      break;
    }
    default:
      m_candle.ClearAnimation(0);
      m_candle.SetLEDs(red, green, blue, white, c_ledOffset, c_ledNum);
      break;
  }
#endif
}