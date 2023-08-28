#ifndef CORES3_GC0308_HPP
#define CORES3_GC0308_HPP

#include <cstdint>

namespace cam { namespace GC0308  {

//! @enum SpecialEffect
enum SpecialEffect : int8_t
{
    NoEffect,  //!< @brief No effect
    Negative,  //!< @brief Negative effect
    Grayscale, //!< @brief Grayscale effect
    RedTint,   //!< @brief Red tint effect
    GreenTint, //!< @brief Green tint effect
    BlueTint,  //!< @brief Blue tint effect
    Sepia,     //!< @brief Sepia effect
};

//! @enum WhiteBalance
enum WhiteBalance : int8_t
{
    Auto,    //!< Automatic
    Sunny,   //!< Manual (Sunny)
    Cloudy,  //!< Manual (Cloudy)
    Office,  //!< Manual (Office)
    Home,    //!< Manual (Home)
};

/*!
  @brief complement esp32-camera GC0308 driver
  @warning Must be call after esp_camera_init() once.
  @note Delete set_gain_ctrl
  @note Add set_agc_gain
  @note Add set_specia_effect
  @note Add set_wb_mode
  @note Replace set_contrast
  @retval true Success
  @retval false Failure
*/
bool complementDriver();

//
}}
#endif
