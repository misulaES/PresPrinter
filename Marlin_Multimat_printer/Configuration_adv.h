/**
		Adaptacion de Marlin para la impresora "UVPRINT" POR  Miguel Surroca Laguardia.
                JULIO 2021
	
	Las inserciones y modificaciones llevan $$ por delante del comentario.
				
				 
C:\Users\Misula\Documents\EXTRUSOR 3D\Programación\Marlin-1.1.x\Marlin\Configuration. 
 *
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * Configuration_adv.h
 *
 * Advanced settings.
 * Only change these if you know exactly what you're doing.
 * Some of these settings can damage your printer if improperly set!
 *
 * Basic settings can be found in Configuration.h
 *
 */
 

 
#ifndef CONFIGURATION_ADV_H
#define CONFIGURATION_ADV_H
#define CONFIGURATION_ADV_H_VERSION 010109




// @section temperature

//===========================================================================
//=============================Thermal Settings  ============================
//===========================================================================

//
// Hephestos 2 24V heated bed upgrade kit.
// https://store.bq.com/en/heated-bed-kit-hephestos2
//
//#define HEPHESTOS2_HEATED_BED_KIT
#if ENABLED(HEPHESTOS2_HEATED_BED_KIT)
  #undef TEMP_SENSOR_BED
  #define TEMP_SENSOR_BED 70
  #define HEATER_BED_INVERTING true
#endif

#if DISABLED(PIDTEMPBED)
  #define BED_CHECK_INTERVAL 5000 // ms between checks in bang-bang control
  #if ENABLED(BED_LIMIT_SWITCHING)
    #define BED_HYSTERESIS 2 // Only disable heating if T>target+BED_HYSTERESIS and enable heating if T>target-BED_HYSTERESIS
  #endif
#endif

/**
  * Protección térmica proporciona protección adicional a su impresora contra daños y fuego.
Marlin siempre incluye rangos seguros de temperatura mínima y máxima que protegen contra un cable de termistor roto o desconectado.
  * *
  * El problema: si se cae un termistor, informará una temperatura mucho más baja, y el firmware mantendrá el calentador encendido.
  * La solución: una vez que la temperatura alcanza el objetivo, comience a observar:
			* Si la temperatura se mantiene muy por debajo del objetivo (histéresis) durante demasiado tiempo (período), el firmware detendrá la máquina como medida de seguridad
			* Si obtiene falsos positivos para "Heating failed", aumente THERMAL_PROTECTION_HYSTERESIS y/o THERMAL_PROTECTION_PERIOD
 */   
#if ENABLED(THERMAL_PROTECTION_HOTENDS)   //Se refiere a variaciones de temperatura ilogicas cuando esta imprimiendo. 
											//Puede ser causa de parada inesperada.
  #define THERMAL_PROTECTION_PERIOD  30      // comprueba cada estos segundos
  #define THERMAL_PROTECTION_HYSTERESIS  3   // si la temperatura se ha alteraDO estos grados

/**
* Cuando un M104, M109 o M303 aumente la temperatura objetivo, el firmware esperará a que expire el WATCH_TEMP_PERIOD.
Si la temperatura no ha aumentado en WATCH_TEMP_INCREASE grados, la máquina se detiene y requiere un restablecimiento completo. 
Esta prueba se reinicia con cualquier M104 / M109 / M303, pero solo si la temperatura actual es lo suficientemente inferior al objetivo para una prueba confiable. (esta programado 15 grados)
* 
* Si obtiene falsos positivos para "Heating failed", aumente WATCH_TEMP_PERIOD y / o disminuir WATCH_TEMP_INCREASE. 
* WATCH_TEMP_INCREASE no debe establecerse por debajo de 2.
*/

// En este caso comprueba si en este tiempo se ha producido al menos este aumento.
  #define WATCH_TEMP_PERIOD 120        // Seconds
  #define WATCH_TEMP_INCREASE 2            // Degrees Celsius
#endif

/**
 * Thermal Protection parameters for the bed are just as above for hotends.
 */
#if ENABLED(THERMAL_PROTECTION_BED)
//$$ Revisar. Igual que el anterior pero para la cama. Puede ser causa de parada.
  #define THERMAL_PROTECTION_BED_PERIOD 20    // Seconds
  #define THERMAL_PROTECTION_BED_HYSTERESIS 2 // Degrees Celsius

  /**
   * As described above, except for the bed (M140/M190/M303).
   */
  #define WATCH_BED_TEMP_PERIOD   30            // Seconds
  #define WATCH_BED_TEMP_INCREASE 1               // Degrees Celsius
#endif

#if ENABLED(PIDTEMP)

 // Lo siguiente agrega un término experimental adicional a la potencia de calentamiento, proporcional a la velocidad de extrusión.
 // si se elige bien Kc, se debe compensar la potencia adicional requerida debido al aumento de la fusión.
 
#define PID_EXTRUSION_SCALING   //$$  se marca intentando corregir el calentamiento producido por un Pid que se calculo sin pasta cuando en la realidad funciona con pasta. 
  #if ENABLED(PID_EXTRUSION_SCALING)  	//$$ ir probando con la practica el valor Kc
    #define DEFAULT_Kc (100) 				//heating power=Kc*(e_speed)
    #define LPQ_MAX_LEN 50
  #endif
#endif

/**				$$ Interesante lo siguiente. Tener en cuenta y probar.
 Inicie el modo de prueba automática con M109 F<factor> S<mintemp> B<maxtemp>
¿Esto puede servir para calcular DEFAULT_Kc ? comprobar

 * Automatic Temperature:
 * The hotend target temperature is calculated by all the buffered lines of gcode.
 * The maximum buffered steps/sec of the extruder motor is called "se".
 * Start autotemp mode with M109 S<mintemp> B<maxtemp> F<factor>
 * The target temperature is set to mintemp+factor*se[steps/sec] and is limited by
 * mintemp and maxtemp. Turn this off by executing M109 without F*
 * Also, if the temperature is set to a value below mintemp, it will not be changed by autotemp.
 * On an Ultimaker, some initial testing worked with M109 S215 B260 F1 in the start.gcode
 */
//#define AUTOTEMP
#if ENABLED(AUTOTEMP)
  #define AUTOTEMP_OLDWEIGHT 0.98
#endif

// Show extra position information in M114
#define M114_DETAIL

// Mostrar valor de temperatura ADC
// Habilite para que M105 incluya valores de ADC leídos de sensores de temperatura.
#define SHOW_TEMP_ADC_VALUES

/**
 * Soporte de termistor de alta temperatura
 * *
 * Los termistores capaces de soportar altas temperaturas tienden a tener dificultades para obtener buenas lecturas a temperatura ambiente y más bajas.
 * Esto significa que HEATER_X_RAW_LO_TEMP probablemente quedará atrapado cuando el elemento calefactor se encienda por primera vez durante el proceso de precalentamiento, lo que activará un min_temp_error como medida de seguridad y forzará la detención de todo.
 * Para evitar esta limitación, permitimos un tiempo de precalentamiento (durante el cual, min_temp_error no se activará) y agregamos un búfer min_temp para manejar lecturas aberrantes.
 * Si desea habilitar esta función para su (s) termistor (es) hotend (s) descomente y establezca valores> 0 en las constantes a continuación
 */

// El número de errores consecutivos de baja temperatura que pueden ocurrir
// antes de que se active un min_temp_error. (No debe ser más de 10.)
#define MAX_CONSECUTIVE_LOW_TEMPERATURE_ERROR_ALLOWED  4

/* El número de milisegundos que un hotend precalentará antes de comenzar a verificar la temperatura.
Este valor NO debe establecerse en el tiempo que tarda el extremo caliente en alcanzar la temperatura objetivo, sino en el tiempo que tarda en alcanzar la temperatura mínima que puede leer su termistor.
Cuanto más bajo, mejor / más seguro.
Esto no debería necesitar más de 30 segundos (30000)
*/
#define MILLISECONDS_PREHEAT_TIME 10000

// @section extruder

// Extruder runout prevention.   ***  NO TIENE EMPLEO EN UVPRINT ****
// If the machine is idle and the temperature over MINTEMP
// then extrude some filament every couple of SECONDS.
//#define EXTRUDER_RUNOUT_PREVENT   //previene caso de estar parada y calentando el filamento. Extruye 5 mm de material cada 30 seg.
#if ENABLED(EXTRUDER_RUNOUT_PREVENT)
  #define EXTRUDER_RUNOUT_MINTEMP 	50
  #define EXTRUDER_RUNOUT_SECONDS 	30
  #define EXTRUDER_RUNOUT_SPEED 		2000  // mm/m
  #define EXTRUDER_RUNOUT_EXTRUDE 	5   // mm
#endif

// @section temperature

// Calibration for AD595 / AD8495 sensor to adjust temperature measurements.
// The final temperature is calculated as (measuredTemp * GAIN) + OFFSET.
#define TEMP_SENSOR_AD595_OFFSET  		0.0
#define TEMP_SENSOR_AD595_GAIN    		1.0
#define TEMP_SENSOR_AD8495_OFFSET 		0.0
#define TEMP_SENSOR_AD8495_GAIN   		1.0

/**
 * Controller Fan
 * To cool down the stepper drivers and MOSFETs.
 *
 * The fan will turn on automatically whenever any stepper is enabled
 * and turn off after a set period after all steppers are turned off.
 */
//#define USE_CONTROLLER_FAN				//$$  definimos un ventilador manejado mediante el pin CONTROLLER_FAN_PIN = 12 a traves de un rele.

#if ENABLED(USE_CONTROLLER_FAN)
  #define CONTROLLER_FAN_PIN  12        // Set a custom pin for the controller fan
  #define CONTROLLERFAN_SECS  60        // Duration in seconds for the fan to run after all motors are disabled
  #define CONTROLLERFAN_SPEED 255       // 255 == full speed
#endif

// When first starting the main fan, run it at full speed for the
// given number of milliseconds.  This gets the fan spinning reliably
// before setting a PWM value. (Does not work with software PWM for fan on Sanguinololu)
//#define FAN_KICKSTART_TIME 100

/**
 * PWM Fan Scaling
 *
 * Define the min/max speeds for PWM fans (as set with M106).
 *
 * With these options the M106 0-255 value range is scaled to a subset
 * to ensure that the fan has enough power to spin, or to run lower
 * current fans with higher current. (e.g., 5V/12V fans with 12V/24V)
 * Value 0 always turns off the fan.
 *
 * Define one or both of these to override the default 0-255 range.
 */
#define FAN_MIN_PWM 50
#define FAN_MAX_PWM 128

// @section extruder

/**
 * Extruder cooling fans
 *
 * Extruder auto fans automatically turn on when their extruders'
 * temperatures go above EXTRUDER_AUTO_FAN_TEMPERATURE.
 *
 * Your board's pins file specifies the recommended pins. Override those here
 * or set to -1 to disable completely.
 *
 * Multiple extruders can be assigned to the same pin in which case
 * the fan will turn on when any selected extruder is above the threshold.
 */
#define E0_AUTO_FAN_PIN 45

#define E1_AUTO_FAN_PIN -1
#define E2_AUTO_FAN_PIN -1
#define E3_AUTO_FAN_PIN -1
#define E4_AUTO_FAN_PIN -1
#define CHAMBER_AUTO_FAN_PIN -1
#define EXTRUDER_AUTO_FAN_TEMPERATURE 50
#define EXTRUDER_AUTO_FAN_SPEED   255  // == full speed

/**
 * Part-Cooling Fan Multiplexer
 *
 * This feature allows you to digitally multiplex the fan output.
 * The multiplexer is automatically switched at tool-change.
 * Set FANMUX[012]_PINs below for up to 2, 4, or 8 multiplexed fans.
 */
//#define FANMUX0_PIN -1		//$$ para un futuro ventilador con enfriador
//#define FANMUX1_PIN -1
//#define FANMUX2_PIN -1

/**
 * M355 Case Light on-off / brightness
 */
//#define CASE_LIGHT_ENABLE
#if ENABLED(CASE_LIGHT_ENABLE)
  //#define CASE_LIGHT_PIN 4                  // Override the default pin if needed
  #define INVERT_CASE_LIGHT false             // Set true if Case Light is ON when pin is LOW
  #define CASE_LIGHT_DEFAULT_ON true          // Set default power-up state on
  #define CASE_LIGHT_DEFAULT_BRIGHTNESS 105   // Set default power-up brightness (0-255, requires PWM pin)
  //#define MENU_ITEM_CASE_LIGHT              // Add a Case Light option to the LCD main menu
  //#define CASE_LIGHT_USE_NEOPIXEL           // Use Neopixel LED as case light, requires NEOPIXEL_LED.
  #if ENABLED(CASE_LIGHT_USE_NEOPIXEL)
    #define CASE_LIGHT_NEOPIXEL_COLOR { 255, 255, 255, 255 } // { Red, Green, Blue, White }
  #endif
#endif

//===========================================================================
//============================ Mechanical Settings ==========================
//===========================================================================

// @section homing

// If you want endstops to stay on (by default) even when not homing
// enable this option. Override at any time with M120, M121.
//#define ENDSTOPS_ALWAYS_ON_DEFAULT

// @section extras

//  $$ OJO esta opcion ahorra corriente pero podria dar problemas de perdida de posicion de la cama. Observar por si hay que deshabilitar.
//#define Z_LATE_ENABLE // Enable Z the last moment. Needed if your Z driver overheats.


// &&  ATENCION Esta opcion puede ser interesante
//Emplee un controlador externo de circuito cerrado que pueda ser activado o desactivado por el controlador principal. 
//Usando un solo cable para la señal de control y otro para la señal de retorno de "movimiento completo" para indicar 
//si el movimiento pudo o no realizarse con éxito.

//#define EXTERNAL_CLOSED_LOOP_CONTROLLER 
#if ENABLED(EXTERNAL_CLOSED_LOOP_CONTROLLER) 
	#define CLOSED_LOOP_ENABLE_PIN -1 
	#define CLOSED_LOOP_MOVE_COMPLETE_PIN -1 
#endif 

/**
 * Dual Steppers / Dual Endstops
 *
 * This section will allow you to use extra E drivers to drive a second motor for X, Y, or Z axes.
 *
 * For example, set X_DUAL_STEPPER_DRIVERS setting to use a second motor. If the motors need to
 * spin in opposite directions set INVERT_X2_VS_X_DIR. If the second motor needs its own endstop
 * set X_DUAL_ENDSTOPS. This can adjust for "racking." Use X2_USE_ENDSTOP to set the endstop plug
 * that should be used for the second endstop. Extra endstops will appear in the output of 'M119'.
 *
 * Use X_DUAL_ENDSTOP_ADJUSTMENT to adjust for mechanical imperfection. After homing both motors
 * this offset is applied to the X2 motor. To find the offset home the X axis, and measure the error
 * in X2. Dual endstop offsets can be set at runtime with 'M666 X<offset> Y<offset> Z<offset>'.
 */
 
/*
* Esta sección le permitirá utilizar controladores E adicionales para conducir un segundo motor para los ejes X, Y o Z.
   * Por ejemplo, establezca la configuración Z_DUAL_STEPPER_DRIVERS para usar un segundo motor. 
   Si los motores necesitan girar en direcciones opuestas configuradas INVERT_Z2_VS_Z_DIR. 
  Si el segundo motor necesita su propio FC establezca X_DUAL_ENDSTOPS. Esto puede ajustarse para "trasiego". 
  Use Z2_USE_ENDSTOP para configurar el FC final que debe usarse para el segundo FC final. 
  Los topes finales adicionales aparecerán en la salida de 'M119'.
  * Use Z_DUAL_ENDSTOP_ADJUSTMENT para ajustar la imperfección mecánica. 
  Después de hacer home (ambos motores) este desplazamiento se aplica adicionalmente al motor Z2. 
  Medir el error de Z2 respecto de Z. Las compensaciones dobles de fin de carrera se pueden establecer en 
  tiempo de ejecución con 'M666 X <compensación> Y <compensación> Z <compensación>'.
 */

//#define X_DUAL_STEPPER_DRIVERS
#if ENABLED(X_DUAL_STEPPER_DRIVERS)
  #define INVERT_X2_VS_X_DIR true   // Set 'true' if X motors should rotate in opposite directions
  //#define X_DUAL_ENDSTOPS
  #if ENABLED(X_DUAL_ENDSTOPS)
    #define X2_USE_ENDSTOP _XMAX_
    #define X_DUAL_ENDSTOPS_ADJUSTMENT  0
  #endif
#endif

//#define Y_DUAL_STEPPER_DRIVERS
#if ENABLED(Y_DUAL_STEPPER_DRIVERS)
  #define INVERT_Y2_VS_Y_DIR false   // Set 'true' if Y motors should rotate in opposite directions
  //#define Y_DUAL_ENDSTOPS
  #if ENABLED(Y_DUAL_ENDSTOPS)
    #define Y2_USE_ENDSTOP _YMAX_
    #define Y_DUAL_ENDSTOPS_ADJUSTMENT  0
  #endif
#endif


//#define Z_DUAL_STEPPER_DRIVERS
#if ENABLED(Z_DUAL_STEPPER_DRIVERS)
  #define INVERT_X2_VS_X_DIR false
  #define Z_DUAL_ENDSTOPS
  #if ENABLED(Z_DUAL_ENDSTOPS)
    #define Z2_USE_ENDSTOP    _YMAX_
	
 //   #define Z_DUAL_ENDSTOPS_ADJUSTMENT 1	//es la distancia de retroceso en mm
  #endif
#endif

/*---nuestro caso-  ....Modificado para MULTIMAT_PRINTER.
	Hacemos una trampa que es usar un ednstop dual para Z pero sin stepper dual. 
	Hacemos una conexion en serie de los dos FC del eje Z minimo. Parece funcionar bien
	Saco esto del bloque de Z_DUAL porque solo me interesa usar el FC y emplear 
	el STEPPER para el extrusor del cartucho.
*/
/*  #define Z_DUAL_ENDSTOPS
	#if ENABLED(Z_DUAL_ENDSTOPS)
		#define Z2_USE_ENDSTOP    _YMAX_
	#endif
*/


// Activate a solenoid on the active extruder with M380. Disable all with M381.
// Define SOL0_PIN, SOL1_PIN, etc., for each extruder that has a solenoid.
//#define EXT_SOLENOID		//OTRA POSIBILIDAD DE CONTROL SOBRE BOMBAS O MOTORES 

// @section homing

// Homing hits each endstop, retracts by these distances, then does a slower bump.
#define X_HOME_BUMP_MM 5   //DISTANCIA DE RETROCESO AL TOPE FIN CARRERA 
#define Y_HOME_BUMP_MM 5
#define Z_HOME_BUMP_MM 3
#define HOMING_BUMP_DIVISOR { 2, 2, 4 }  // Re-Bump Speed Divisor (Divides the Homing Feedrate)

#define QUICK_HOME                     // If homing includes X and Y, do a diagonal move initially

// When G28 is called, this option will make Y home before X
//#define HOME_Y_BEFORE_X

// Enable this if X or Y can't home without homing the other axis first.
//#define CODEPENDENT_XY_HOMING



// @section machine

#define AXIS_RELATIVE_MODES {false, false, false, false}  

// Allow duplication mode with a basic dual-nozzle extruder
//#define DUAL_NOZZLE_DUPLICATION_MODE

// By default pololu step drivers require an active high signal. 
// However, some high power drivers require an active low signal as step.
#define INVERT_X_STEP_PIN false
#define INVERT_Y_STEP_PIN false
#define INVERT_Z_STEP_PIN false
#define INVERT_E_STEP_PIN false

// Default stepper release if idle. Set to 0 to deactivate.
// Steppers will shut down DEFAULT_STEPPER_DEACTIVE_TIME seconds after the last move when DISABLE_INACTIVE_? is true.
// Time can be set by M18 and M84.
#define DEFAULT_STEPPER_DEACTIVE_TIME 25   //SEGUNDOS
#define DISABLE_INACTIVE_X true
#define DISABLE_INACTIVE_Y true
#define DISABLE_INACTIVE_Z true  // set to false if the nozzle will fall down on your printed part when print has finished.
#define DISABLE_INACTIVE_E true

#define DEFAULT_MINIMUMFEEDRATE       0.0     // minimum feedrate
#define DEFAULT_MINTRAVELFEEDRATE     0.0

#define HOME_AFTER_DEACTIVATE  // $$ si se activa lo anterior habra que activar esto. Require rehoming after steppers are deactivated

// @section lcd

#if ENABLED(ULTIPANEL)
  #define MANUAL_FEEDRATE {50*60, 50*60, 2*60,60} // Feedrates for manual moves along X, Y, Z, E from panel
  #define ULTIPANEL_FEEDMULTIPLY  // Comment to disable setting feedrate multiplier via encoder
#endif

// @section extras

// minimum time in microseconds that a movement needs to take if the buffer is emptied.
//#define DEFAULT_MINSEGMENTTIME        20000  // este es el valor original
#define DEFAULT_MINSEGMENTTIME        25000

// If defined the movements slow down when the look ahead buffer is only half full
#define SLOWDOWN

// Frequency limit
// See nophead's blog for more info
// Not working O
//#define XY_FREQUENCY_LIMIT  15

// Minimum planner junction speed. Sets the default minimum speed the planner plans for at the end
// of the buffer and all stops. This should not be much greater than zero and should only be changed
// if unwanted behavior is observed on a user's machine when running at very slow speeds.
#define MINIMUM_PLANNER_SPEED 0.05 // (mm/sec)

//
// Use Junction Deviation instead of traditional Jerk Limiting
//
//#define JUNCTION_DEVIATION
#if ENABLED(JUNCTION_DEVIATION)
  #define JUNCTION_DEVIATION_MM 0.02  // (mm) Distance from real junction edge
#endif

/**
 * Adaptive Step Smoothing increases the resolution of multi-axis moves, particularly at step frequencies
 * below 1kHz (for AVR) or 10kHz (for ARM), where aliasing between axes in multi-axis moves causes audible
 * vibration and surface artifacts. The algorithm adapts to provide the best possible step smoothing at the
 * lowest stepping frequencies.
 */
#define ADAPTIVE_STEP_SMOOTHING

// Microstep setting (Only functional when stepper driver microstep pins are connected to MCU.
//#define MICROSTEP_MODES { 32, 32, 32, 4, 32 } // [1,2,4,8,16]  

//===========================================================================
//=============================Additional Features===========================
//===========================================================================

#define ENCODER_RATE_MULTIPLIER         // If defined, certain menu edit operations automatically multiply the steps when the encoder is moved quickly
#define ENCODER_10X_STEPS_PER_SEC 60   // If the encoder steps per sec exceeds this value, multiply steps moved x10 to quickly advance the value
#define ENCODER_100X_STEPS_PER_SEC 120  // If the encoder steps per sec exceeds this value, multiply steps moved x100 to really quickly advance the value

//#define CHDK 4        //Pin for triggering CHDK to take a picture see how to use it here http://captain-slow.dk/2014/03/09/3d-printing-timelapses/
#define CHDK_DELAY 50 //How long in ms the pin should stay HIGH before going LOW again

// @section lcd

// Include a page of printer information in the LCD Main Menu
//#define LCD_INFO_MENU

// Scroll a longer status message into view
//#define STATUS_MESSAGE_SCROLLING

// On the Info Screen, display XY with one decimal place when possible
//#define LCD_DECIMAL_SMALL_XY

// The timeout (in ms) to return to the status screen from sub-menus
//#define LCD_TIMEOUT_TO_STATUS 15000

// Add an 'M73' G-code to set the current percentage
//#define LCD_SET_PROGRESS_MANUALLY

#if ENABLED(SDSUPPORT) || ENABLED(LCD_SET_PROGRESS_MANUALLY)
//#define LCD_PROGRESS_BAR              // Show a progress bar on HD44780 LCDs for SD printing
  #if ENABLED(LCD_PROGRESS_BAR)
    #define PROGRESS_BAR_BAR_TIME 2000    // (ms) Amount of time to show the bar
    #define PROGRESS_BAR_MSG_TIME 3000    // (ms) Amount of time to show the status message
    #define PROGRESS_MSG_EXPIRE   0       // (ms) Amount of time to retain the status message (0=forever)
    //#define PROGRESS_MSG_ONCE           // Show the message for MSG_TIME then clear it
    //#define LCD_PROGRESS_BAR_TEST       // Add a menu item to test the progress bar
  #endif
#endif // SDSUPPORT || LCD_SET_PROGRESS_MANUALLY

/**
 * LED Control Menu
 * Enable this feature to add LED Control to the LCD menu
 */
//#define LED_CONTROL_MENU
#if ENABLED(LED_CONTROL_MENU)
  #define LED_COLOR_PRESETS                 // Enable the Preset Color menu option
  #if ENABLED(LED_COLOR_PRESETS)
    #define LED_USER_PRESET_RED        255  // User defined RED value
    #define LED_USER_PRESET_GREEN      128  // User defined GREEN value
    #define LED_USER_PRESET_BLUE         0  // User defined BLUE value
    #define LED_USER_PRESET_WHITE      255  // User defined WHITE value
    #define LED_USER_PRESET_BRIGHTNESS 255  // User defined intensity
    //#define LED_USER_PRESET_STARTUP       // Have the printer display the user preset color on startup
  #endif
#endif // LED_CONTROL_MENU

#if ENABLED(SDSUPPORT)

  // Some RAMPS and other boards don't detect when an SD card is inserted. You can work
  // around this by connecting a push button or single throw switch to the pin defined
  // as SD_DETECT_PIN in your board's pins definitions.
  // This setting should be disabled unless you are using a push button, pulling the pin to ground.
  // Note: This is always disabled for ULTIPANEL (except ELB_FULL_GRAPHIC_CONTROLLER).
  //#define SD_DETECT_INVERTED

  #define SD_FINISHED_STEPPERRELEASE true          // Disable steppers when SD Print is finished
  #define SD_FINISHED_RELEASECOMMAND "M84 X Y Z E" // You might want to keep the z enabled so your bed stays in place.

  // Reverse SD sort to show "more recent" files first, according to the card's FAT.
  // Since the FAT gets out of order with usage, SDCARD_SORT_ALPHA is recommended.
  #define SDCARD_RATHERRECENTFIRST

  // Add an option in the menu to run all auto#.g files
  //#define MENU_ADDAUTOSTART

  /**
   * Continue after Power-Loss (Creality3D)
   *
   * Store the current state to the SD Card at the start of each layer
   * during SD printing. If the recovery file is found at boot time, present
   * an option on the LCD screen to continue the print from the last-known
   * point in the file.
   */
  //#define POWER_LOSS_RECOVERY
  #if ENABLED(POWER_LOSS_RECOVERY)
    //#define POWER_LOSS_PIN   44     // Pin to detect power loss
    //#define POWER_LOSS_STATE HIGH   // State of pin indicating power loss
  #endif

  /**
   * Sort SD file listings in alphabetical order.
   *
   * With this option enabled, items on SD cards will be sorted
   * by name for easier navigation.
   *
   * By default...
   *
   *  - Use the slowest -but safest- method for sorting.
   *  - Folders are sorted to the top.
   *  - The sort key is statically allocated.
   *  - No added G-code (M34) support.
   *  - 40 item sorting limit. (Items after the first 40 are unsorted.)
   *
   * SD sorting uses static allocation (as set by SDSORT_LIMIT), allowing the
   * compiler to calculate the worst-case usage and throw an error if the SRAM
   * limit is exceeded.
   *
   *  - SDSORT_USES_RAM provides faster sorting via a static directory buffer.
   *  - SDSORT_USES_STACK does the same, but uses a local stack-based buffer.
   *  - SDSORT_CACHE_NAMES will retain the sorted file listing in RAM. (Expensive!)
   *  - SDSORT_DYNAMIC_RAM only uses RAM when the SD menu is visible. (Use with caution!)
   */

 #define SDCARD_SORT_ALPHA
  // SD Card Sorting options
  #if ENABLED(SDCARD_SORT_ALPHA)
    #define SDSORT_LIMIT       40     // Maximum number of sorted items (10-256). Costs 27 bytes each.
    #define FOLDER_SORTING     -1     // -1=above  0=none  1=below
    #define SDSORT_GCODE       false  // Allow turning sorting on/off with LCD and M34 g-code.
    #define SDSORT_USES_RAM    false  // Pre-allocate a static array for faster pre-sorting.
    #define SDSORT_USES_STACK  false  // Prefer the stack for pre-sorting to give back some SRAM. (Negated by next 2 options.)
    #define SDSORT_CACHE_NAMES false  // Keep sorted items in RAM longer for speedy performance. Most expensive option.
    #define SDSORT_DYNAMIC_RAM false  // Use dynamic allocation (within SD menus). Least expensive option. Set SDSORT_LIMIT before use!
    #define SDSORT_CACHE_VFATS 2      // Maximum number of 13-byte VFAT entries to use for sorting.
                                      // Note: Only affects SCROLL_LONG_FILENAMES with SDSORT_CACHE_NAMES but not SDSORT_DYNAMIC_RAM.
  #endif

  // This allows hosts to request long names for files and folders with M33
  #define LONG_FILENAME_HOST_SUPPORT

  // Enable this option to scroll long filenames in the SD card menu
  #define SCROLL_LONG_FILENAMES

  /**
   * This option allows you to abort SD printing when any endstop is triggered.
   * This feature must be enabled with "M540 S1" or from the LCD menu.
   * To have any effect, endstops must be enabled during SD printing.
   */
  #define ABORT_ON_ENDSTOP_HIT_FEATURE_ENABLED

  /**
   * This option makes it easier to print the same SD Card file again.
   * On print completion the LCD Menu will open with the file selected.
   * You can just click to start the print, or navigate elsewhere.
   */
  //#define SD_REPRINT_LAST_SELECTED_FILE

  /**
   * Auto-report SdCard status with M27 S<seconds>
   */
  //#define AUTO_REPORT_SD_STATUS

#endif // SDSUPPORT

/**
 * Additional options for Graphical Displays
 *
 * Use the optimizations here to improve printing performance,
 * which can be adversely affected by graphical display drawing,
 * especially when doing several short moves, and when printing
 * on DELTA and SCARA machines.
 *
 * Some of these options may result in the display lagging behind
 * controller events, as there is a trade-off between reliable
 * printing performance versus fast display updates.
 */
#if ENABLED(DOGLCD)
  // Show SD percentage next to the progress bar
  //#define DOGM_SD_PERCENT

  // Enable to save many cycles by drawing a hollow frame on the Info Screen
  #define XYZ_HOLLOW_FRAME

  // Enable to save many cycles by drawing a hollow frame on Menu Screens
  #define MENU_HOLLOW_FRAME

  // A bigger font is available for edit items. Costs 3120 bytes of PROGMEM.
  // Western only. Not available for Cyrillic, Kana, Turkish, Greek, or Chinese.
  //#define USE_BIG_EDIT_FONT

  // A smaller font may be used on the Info Screen. Costs 2300 bytes of PROGMEM.
  // Western only. Not available for Cyrillic, Kana, Turkish, Greek, or Chinese.
  //#define USE_SMALL_INFOFONT

  // Enable this option and reduce the value to optimize screen updates.
  // The normal delay is 10µs. Use the lowest value that still gives a reliable display.
  //#define DOGM_SPI_DELAY_US 5

  // Swap the CW/CCW indicators in the graphics overlay
  //#define OVERLAY_GFX_REVERSE

  #if ENABLED(U8GLIB_ST7920)
    /**
     * ST7920-based LCDs can emulate a 16 x 4 character display using
     * the ST7920 character-generator for very fast screen updates.
     * Enable LIGHTWEIGHT_UI to use this special display mode.
     *
     * Since LIGHTWEIGHT_UI has limited space, the position and status
     * message occupy the same line. Set STATUS_EXPIRE_SECONDS to the
     * length of time to display the status message before clearing.
     *
     * Set STATUS_EXPIRE_SECONDS to zero to never clear the status.
     * This will prevent position updates from being displayed.
     */
    //#define LIGHTWEIGHT_UI
    #if ENABLED(LIGHTWEIGHT_UI)
      #define STATUS_EXPIRE_SECONDS 20
    #endif
  #endif

#endif // DOGLCD

// @section safety

// The hardware watchdog should reset the microcontroller disabling all outputs,
// in case the firmware gets stuck and doesn't do temperature regulation.
//#define USE_WATCHDOG

#if ENABLED(USE_WATCHDOG)
  // If you have a watchdog reboot in an ArduinoMega2560 then the device will hang forever, as a watchdog reset will leave the watchdog on.
  // The "WATCHDOG_RESET_MANUAL" goes around this by not using the hardware reset.
  //  However, THIS FEATURE IS UNSAFE!, as it will only work if interrupts are disabled. And the code could hang in an interrupt routine with interrupts disabled.
  #define WATCHDOG_RESET_MANUAL
#endif

// @section lcd

/**
 * Babystepping enables movement of the axes by tiny increments without changing
 * the current position values. This feature is used primarily to adjust the Z
 * axis in the first layer of a print in real-time.
 *
 * Babystepping permite el movimiento de los ejes en pequeños incrementos sin cambiar 
 los valores de posición actuales. Esta función se utiliza principalmente para ajustar 
 el eje Z en la primera capa de una impresión en tiempo real.
 * Warning: Does not respect endstops!
 */
//#define BABYSTEPPING
#if ENABLED(BABYSTEPPING)
  //#define BABYSTEP_XY              // Also enable X/Y Babystepping. Not supported on DELTA!
  #define BABYSTEP_INVERT_Z false    // Change if Z babysteps should go the other way
  #define BABYSTEP_MULTIPLICATOR 1   // Babysteps are very small. Increase for faster motion.
  //#define BABYSTEP_ZPROBE_OFFSET   // Enable to combine M851 and Babystepping
  //#define DOUBLECLICK_FOR_Z_BABYSTEPPING // Double-click on the Status Screen for Z Babystepping.
  #define DOUBLECLICK_MAX_INTERVAL 1250 // Maximum interval between clicks, in milliseconds.
                                        // Note: Extra time may be added to mitigate controller latency.
  //#define BABYSTEP_ZPROBE_GFX_OVERLAY // Enable graphical overlay on Z-offset editor
#endif

// @section extruder

/**
 * Linear Pressure Control v1.5
 *
 * Assumption: advance [steps] = k * (delta velocity [steps/s])
 * K=0 means advance disabled.
 *
 * NOTE: K values for LIN_ADVANCE 1.5 differ from earlier versions!
 *
 * Set K around 0.22 for 3mm PLA Direct Drive with ~6.5cm between the drive gear and heatbreak.
 * Larger K values will be needed for flexible filament and greater distances.
 * If this algorithm produces a higher speed offset than the extruder can handle (compared to E jerk)
 * print acceleration will be reduced during the affected moves to keep within the limit.
 *
 * See http://marlinfw.org/docs/features/lin_advance.html for full instructions.
 * Mention @Sebastianv650 on GitHub to alert the author of any issues.
 */
 
 
//#define LIN_ADVANCE
#if ENABLED(LIN_ADVANCE)
  #define LIN_ADVANCE_K 0.22  // Unit: mm compression per 1mm/s extruder speed
  #define LA_DEBUG          // If enabled, this will generate debug information output over USB.
#endif

// @section leveling

#if ENABLED(MESH_BED_LEVELING) || ENABLED(AUTO_BED_LEVELING_UBL)
  // Override the mesh area if the automatic (max) area is too large
  //#define MESH_MIN_X MESH_INSET
  //#define MESH_MIN_Y MESH_INSET
  //#define MESH_MAX_X X_BED_SIZE - (MESH_INSET)
  //#define MESH_MAX_Y Y_BED_SIZE - (MESH_INSET)
#endif

// @section extras

//
// G2/G3 Arc Support
//
#define ARC_SUPPORT               // Disable this feature to save ~3226 bytes
#if ENABLED(ARC_SUPPORT)
  #define MM_PER_ARC_SEGMENT  2   // Length of each arc segment
  #define N_ARC_CORRECTION   25   // Number of intertpolated segments between corrections
  //#define ARC_P_CIRCLES         // Enable the 'P' parameter to specify complete circles
  //#define CNC_WORKSPACE_PLANES  // Allow G2/G3 to operate in XY, ZX, or YZ planes
#endif

// Support for G5 with XYZE destination and IJPQ offsets. Requires ~2666 bytes.
//#define BEZIER_CURVE_SUPPORT

// G38.2 and G38.3 Probe Target
// Set MULTIPLE_PROBING if you want G38 to double touch
//#define G38_PROBE_TARGET
#if ENABLED(G38_PROBE_TARGET)
  #define G38_MINIMUM_MOVE 0.0275 // minimum distance in mm that will produce a move (determined using the print statement in check_move)
#endif

// Moves (or segments) with fewer steps than this will be joined with the next move
#define MIN_STEPS_PER_SEGMENT 6

/**
 * Minimum delay after setting the stepper DIR (in ns)
 *     0 : No delay (Expect at least 10µS since one Stepper ISR must transpire)
 *    20 : Minimum for TMC2xxx drivers
 *   200 : Minimum for A4988 drivers
 *   500 : Minimum for LV8729 drivers (guess, no info in datasheet)
 *   650 : Minimum for DRV8825 drivers    ********ESTE ES EL USADO************
 *  1500 : Minimum for TB6600 drivers (guess, no info in datasheet)
 * 15000 : Minimum for TB6560 drivers (guess, no info in datasheet)
 *
 * Override the default value based on the driver type set in Configuration.h.
 */
#define MINIMUM_STEPPER_DIR_DELAY 650      //Ojo son nanosegundos  = 0,650 microsegundos SE USA CUANDO HAY UN CAMBIO DE DIRECCION

/**
 * Minimum stepper driver pulse width (in µs)
 *   0 : Smallest possible width the MCU can produce, compatible with TMC2xxx drivers
 *   1 : Minimum for A4988 stepper drivers
 *   1 : Minimum for LV8729 stepper drivers
 *   2 : Minimum for DRV8825 stepper drivers
 *   3 : Minimum for TB6600 stepper drivers
 *  30 : Minimum for TB6560 stepper drivers
 *
 * Override the default value based on the driver type set in Configuration.h.
 */
#define MINIMUM_STEPPER_PULSE  2    //

/**
 * Maximum stepping rate (in Hz) the stepper driver allows
 *  If undefined, defaults to 1MHz / (2 * MINIMUM_STEPPER_PULSE)
 *  500000 : Maximum for A4988 stepper driver
 *  400000 : Maximum for TMC2xxx stepper drivers
 *  250000 : Maximum for DRV8825 stepper driver
 *  150000 : Maximum for TB6600 stepper driver
 *  130000 : Maximum for LV8729 stepper driver
 *   15000 : Maximum for TB6560 stepper driver
 *
 * Override the default value based on the driver type set in Configuration.h.
 */
#define MAXIMUM_STEPPER_RATE 250000

// @section temperature

// Control heater 0 and heater 1 in parallel.
//#define HEATERS_PARALLEL

//===========================================================================
//================================= Buffers =================================
//===========================================================================

// @section hidden

// The number of linear motions that can be in the plan at any give time.
// THE BLOCK_BUFFER_SIZE NEEDS TO BE A POWER OF 2 (e.g. 8, 16, 32) because shifts and ors are used to do the ring-buffering.
#if ENABLED(SDSUPPORT)
  #define BLOCK_BUFFER_SIZE 16 // SD,LCD,Buttons take more memory, block buffer needs to be smaller
#else
  #define BLOCK_BUFFER_SIZE 16 // maximize block buffer
#endif

// @section serial

// The ASCII buffer for serial input
#define MAX_CMD_SIZE 96
#define BUFSIZE 4

// Transmission to Host Buffer Size
// To save 386 bytes of PROGMEM (and TX_BUFFER_SIZE+3 bytes of RAM) set to 0.
// To buffer a simple "ok" you need 4 bytes.
// For ADVANCED_OK (M105) you need 32 bytes.
// For debug-echo: 128 bytes for the optimal speed.
// Other output doesn't need to be that speedy.
// :[0, 2, 4, 8, 16, 32, 64, 128, 256]
#define TX_BUFFER_SIZE 0

// Host Receive Buffer Size
// Without XON/XOFF flow control (see SERIAL_XON_XOFF below) 32 bytes should be enough.
// To use flow control, set this buffer size to at least 1024 bytes.
// :[0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048]
//#define RX_BUFFER_SIZE 1024

#if RX_BUFFER_SIZE >= 1024
  // Enable to have the controller send XON/XOFF control characters to
  // the host to signal the RX buffer is becoming full.
  //#define SERIAL_XON_XOFF
#endif

#if ENABLED(SDSUPPORT)
  // Enable this option to collect and display the maximum
  // RX queue usage after transferring a file to SD.
  //#define SERIAL_STATS_MAX_RX_QUEUED

  // Enable this option to collect and display the number
  // of dropped bytes after a file transfer to SD.
  //#define SERIAL_STATS_DROPPED_RX
#endif

// Enable an emergency-command parser to intercept certain commands as they
// enter the serial receive buffer, so they cannot be blocked.
// Currently handles M108, M112, M410
// Does not work on boards using AT90USB (USBCON) processors!
#define EMERGENCY_PARSER

// Bad Serial-connections can miss a received command by sending an 'ok'
// Therefore some clients abort after 30 seconds in a timeout.
// Some other clients start sending commands while receiving a 'wait'.
// This "wait" is only sent when the buffer is empty. 1 second is a good value here.
//#define NO_TIMEOUTS 1000 // Milliseconds

// Some clients will have this feature soon. This could make the NO_TIMEOUTS unnecessary.
//#define ADVANCED_OK

// @section extras

/**
 * Firmware-based and LCD-controlled retract
 *
 * Add G10 / G11 commands for automatic firmware-based retract / recover.
 * Use M207 and M208 to define parameters for retract / recover.
 *
 * Use M209 to enable or disable auto-retract.
 * With auto-retract enabled, all G1 E moves within the set range
 * will be converted to firmware-based retract/recover moves.
 *
 * Be sure to turn off auto-retract during filament change.
 *
 * Note that M207 / M208 / M209 settings are saved to EEPROM.
 *  
 */
//#define FWRETRACT  // Para la opcion PRESPRINT no tiene retracciones pues no puede disminuir presion el la boquilla

//				ATENCION !! 
//	son valores para UVPRINT (version tornillo), donde se considera el hilo de un diametro igual al de la boquilla.

#if ENABLED(FWRETRACT)
  #define MIN_AUTORETRACT 2			// Cuando la retracción automática está activada, convierte E movimientos de esta longitud y más
  #define MAX_AUTORETRACT 4			// Límite superior para la conversión de retracción automática (siempre mayor que MIN_AUTORETRACT)
  #define RETRACT_LENGTH 3			// Longitud de retracción predeterminada (mm positivos)
  #define RETRACT_FEEDRATE 70			// Velocidad de avance predeterminada para retraer (mm / s)
  #define RETRACT_ZLIFT 1				// Default retract Z-lift $$ teoricamente no hace falta que se mueva Z
  #define RETRACT_RECOVER_LENGTH 0.5 	// Longitud de recuperación adicional predeterminada (mm, agregada para retraer la longitud al recuperar)
  #define RETRACT_RECOVER_FEEDRATE 70 // Velocidad de avance por defecto para recuperarse de la retracción (mm / s)
	
	// estas no se usan
  #define RETRACT_LENGTH_SWAP 13          // Default swap retract length (positive mm), for extruder change
  #define RETRACT_RECOVER_LENGTH_SWAP 0   // Default additional swap recover length (mm, added to retract length when recovering from extruder change)
  #define RETRACT_RECOVER_FEEDRATE_SWAP 20 // Default feedrate for recovering from swap retraction (mm/s)
#endif

/**
 * Extra Fan Speed
 * Adds a secondary fan speed for each print-cooling fan.
 *   'M106 P<fan> T3-255' : Set a secondary speed for <fan>
 *   'M106 P<fan> T2'     : Use the set secondary speed
 *   'M106 P<fan> T1'     : Restore the previous fan speed
 */
//#define EXTRA_FAN_SPEED


/**
 * Advanced Pause
 * Experimental feature for filament change support and for parking the nozzle when paused.
 * Adds the GCode M600 for initiating filament change.
 * If PARK_HEAD_ON_PAUSE enabled, adds the GCode M125 to pause printing and park the nozzle.
 *
 * Requires an LCD display.
 * Requires NOZZLE_PARK_FEATURE.
 * This feature is required for the default FILAMENT_RUNOUT_SCRIPT.
 */

//#define ADVANCED_PAUSE_FEATURE    //no se necesita en UVPRINT
#if ENABLED(ADVANCED_PAUSE_FEATURE)
  #define PAUSE_PARK_RETRACT_FEEDRATE         60  // (mm/s) Initial retract feedrate.
  #define PAUSE_PARK_RETRACT_LENGTH            2  // (mm) Initial retract.
                                                  // This short retract is done immediately, before parking the nozzle.
  #define FILAMENT_CHANGE_UNLOAD_FEEDRATE     10  // (mm/s) Unload filament feedrate. This can be pretty fast.
  #define FILAMENT_CHANGE_UNLOAD_ACCEL        25  // (mm/s^2) Lower acceleration may allow a faster feedrate.
  #define FILAMENT_CHANGE_UNLOAD_LENGTH      100  // (mm) The length of filament for a complete unload.
                                                  //   For Bowden, the full length of the tube and nozzle.
                                                  //   For direct drive, the full length of the nozzle.
                                                  //   Set to 0 for manual unloading.
  #define FILAMENT_CHANGE_SLOW_LOAD_FEEDRATE   6  // (mm/s) Slow move when starting load.
  #define FILAMENT_CHANGE_SLOW_LOAD_LENGTH     0  // (mm) Slow length, to allow time to insert material.
                                                  // 0 to disable start loading and skip to fast load only
  #define FILAMENT_CHANGE_FAST_LOAD_FEEDRATE   6  // (mm/s) Load filament feedrate. This can be pretty fast.
  #define FILAMENT_CHANGE_FAST_LOAD_ACCEL     25  // (mm/s^2) Lower acceleration may allow a faster feedrate.
  #define FILAMENT_CHANGE_FAST_LOAD_LENGTH     0  // (mm) Load length of filament, from extruder gear to nozzle.
                                                  //   For Bowden, the full length of the tube and nozzle.
                                                  //   For direct drive, the full length of the nozzle.
  //#define ADVANCED_PAUSE_CONTINUOUS_PURGE       // Purge continuously up to the purge length until interrupted.
  #define ADVANCED_PAUSE_PURGE_FEEDRATE        3  // (mm/s) Extrude feedrate (after loading). Should be slower than load feedrate.
  #define ADVANCED_PAUSE_PURGE_LENGTH         50  // (mm) Length to extrude after loading.
                                                  //   Set to 0 for manual extrusion.
                                                  //   Filament can be extruded repeatedly from the Filament Change menu
                                                  //   until extrusion is consistent, and to purge old filament.

                                                  // Filament Unload does a Retract, Delay, and Purge first:
  #define FILAMENT_UNLOAD_RETRACT_LENGTH      13  // (mm) Unload initial retract length.
  #define FILAMENT_UNLOAD_DELAY             	5000  // (ms) Delay for the filament to cool after retract.
  #define FILAMENT_UNLOAD_PURGE_LENGTH         8  // (mm) An unretract is done, then this length is purged.

  #define PAUSE_PARK_NOZZLE_TIMEOUT           45  // (seconds) Time limit before the nozzle is turned off for safety.
  #define FILAMENT_CHANGE_ALERT_BEEPS         10  // Number of alert beeps to play when a response is needed.
  #define PAUSE_PARK_NO_STEPPER_TIMEOUT           // Enable for XYZ steppers to stay powered on during filament change.

  //#define PARK_HEAD_ON_PAUSE                    // Park the nozzle during pause and filament change.
  //#define HOME_BEFORE_FILAMENT_CHANGE           // Ensure homing has been completed prior to parking for filament change

//  #define FILAMENT_LOAD_UNLOAD_GCODES           // Add M701/M702 Load/Unload G-codes, plus Load/Unload in the LCD Prepare menu.
  //#define FILAMENT_UNLOAD_ALL_EXTRUDERS         // Allow M702 to unload all extruders above a minimum target temp (as set by M302)
#endif


// @section i2cbus

//#define EXPERIMENTAL_I2CBUS
#define I2C_SLAVE_ADDRESS  0 // Set a value from 8 to 127 to act as a slave

// @section extras



/**
 * Filament Width Sensor
 *
 * Measures the filament width in real-time and adjusts
 * flow rate to compensate for any irregularities.
 *
 * Also allows the measured filament diameter to set the
 * extrusion rate, so the slicer only has to specify the
 * volume.
 *
 * Only a single extruder is supported at this time.
 *
 *  34 RAMPS_14    : Analog input 5 on the AUX2 connector
 *  81 PRINTRBOARD : Analog input 2 on the Exp1 connector (version B,C,D,E)
 * 301 RAMBO       : Analog input 3
 *
 * Note: May require analog pins to be defined for other boards.
 */
//#define FILAMENT_WIDTH_SENSOR  //$$ Se activa solo para que la extrusión volumétrica sea el método predeterminado, DEFAULT_NOMINAL_FILAMENT_DIA 

#if ENABLED(FILAMENT_WIDTH_SENSOR)
  #define FILAMENT_SENSOR_EXTRUDER_NUM 0    // Index of the extruder that has the filament sensor. :[0,1,2,3,4]
  #define MEASUREMENT_DELAY_CM        2   // (cm) The distance from the filament sensor to the melting chamber

  #define FILWIDTH_ERROR_MARGIN        1.0  // (mm) If a measurement differs too much from nominal width ignore it
 #define MAX_MEASUREMENT_DELAY       20    // (bytes) Buffer size for stored measurements (1 byte per cm). Must be larger than MEASUREMENT_DELAY_CM.

  #define DEFAULT_MEASURED_FILAMENT_DIA DEFAULT_NOMINAL_FILAMENT_DIA   // Set measured to nominal initially

  // Display filament width on the LCD status line. Status messages will expire after 5 seconds.
  //#define FILAMENT_LCD_DISPLAY
#endif

/**
 * CNC Coordinate Systems
 *
 * Enables G53 and G54-G59.3 commands to select coordinate systems
 * and G92.1 to reset the workspace to native machine space.
 */
//#define CNC_COORDINATE_SYSTEMS

/**
 * M43 - display pin status, watch pins for changes, watch endstops & toggle LED, Z servo probe test, toggle pins
 */
#define PINS_DEBUGGING

/**
 * Auto-report temperatures with M155 S<seconds>
 */
#define AUTO_REPORT_TEMPERATURES

/**
 * Include capabilities in M115 output
 */
#define EXTENDED_CAPABILITIES_REPORT

/**
 * Disable all Volumetric extrusion options
 $$ Trabajamos con extrusion volumetrica por lo que definimos VOLUMETRIC_DEFAULT_ON
 */
//#define NO_VOLUMETRICS		//para UVPRINT se define como NO_VOLUMETRICS. Pero si se utilizan los diametros 
							//de hilo para poner el diametro de boquilla y el factor de extrusion

#if DISABLED(NO_VOLUMETRICS)
  /**
   * Volumetric extrusion default state
   * Activate to make volumetric extrusion the default method,
   * with DEFAULT_NOMINAL_FILAMENT_DIA as the default diameter.
   *
   * M200 D0 to disable, M200 Dn to set a new diameter.
   */
  #define VOLUMETRIC_DEFAULT_ON
#endif

/**
 * Enable this option for a leaner build of Marlin that removes all
 * workspace offsets, simplifying coordinate transformations, leveling, etc.
 *
 *  - M206 and M428 are disabled.
 *  - G92 will revert to its behavior from Marlin 1.0.
 */
#define NO_WORKSPACE_OFFSETS

/**
 * Set the number of proportional font spaces required to fill up a typical character space.
 * This can help to better align the output of commands like `G29 O` Mesh Output.
 *
 * For clients that use a fixed-width font (like OctoPrint), leave this set to 1.0.
 * Otherwise, adjust according to your client and font.
 */
#define PROPORTIONAL_FONT_RATIO 1.0

/**
 * Spend 28 bytes of SRAM to optimize the GCode parser
 */
//#define FASTER_GCODE_PARSER

/**
 * User-defined menu items that execute custom GCode
 */
#define CUSTOM_USER_MENUS
#if ENABLED(CUSTOM_USER_MENUS)
 // #define USER_SCRIPT_DONE "M117 User Script Done"  //creo que es para crear un menu desde LCD
  #define USER_SCRIPT_AUDIBLE_FEEDBACK
  #define USER_SCRIPT_RETURN  // Return to status screen after a script

  #define USER_DESC_1 "Limpia boquilla"
  #define USER_GCODE_1 "G12"
  
#if ENABLED(PRESPRINT)
	#define USER_DESC_3 "Marcha Compresor"
	#define USER_GCODE_3 "G10"
	#define USER_DESC_4 "Para Compresor"
	#define USER_GCODE_4 "G11"	  
#endif
	
#if ENABLED(FWRETRACT)    
	  #define USER_DESC_3 "Retraccion"
	  #define USER_GCODE_3 "G10"
	  #define USER_DESC_4 "Recup. retraccion"
	  #define USER_GCODE_4 "G11"
#endif 

  #define USER_DESC_5 "Centrar carro"
  #define USER_GCODE_5 "M9"  
  
  #if ENABLED(EXTRUSOR_MIX)
	#define USER_DESC_2 "Reset UVPRINT"
	#define USER_GCODE_2 "M10"
  #endif
 
 /*
  #define USER_DESC_3 "Montar cartucho"
  #define USER_GCODE_3 "M14 S1"
 
  #define USER_DESC_4 "Desmontar cartucho"
  #define USER_GCODE_4 "M14 S-1"


  #define USER_DESC_5 "Limpieza"
  #define USER_GCODE_5 "G13"  
    
  #define USER_DESC_6 "Calibracion"
  #define USER_GCODE_6 "M15 D1 V100"  
  
  #define USER_DESC_7 "Servos "
  #define USER_GCODE_7 "M12"  

*/

#endif

/**
 * Specify an action command to send to the host when the printer is killed.
 * Will be sent in the form '//action:ACTION_ON_KILL', e.g. '//action:poweroff'.
 * The host must be configured to handle the action command.
 */
#define ACTION_ON_KILL "poweroff"

/**
 * Specify an action command to send to the host on pause and resume.
 * Will be sent in the form '//action:ACTION_ON_PAUSE', e.g. '//action:pause'.
 * The host must be configured to handle the action command.
 */
//#define ACTION_ON_PAUSE "pause"
//#define ACTION_ON_RESUME "resume"

//===========================================================================
//====================== I2C Position Encoder Settings ======================
//===========================================================================

/**
 *  I2C position encoders for closed loop control.
 *  Developed by Chris Barr at Aus3D.
 *
 *  Wiki: http://wiki.aus3d.com.au/Magnetic_Encoder
 *  Github: https://github.com/Aus3D/MagneticEncoder
 *
 *  Supplier: http://aus3d.com.au/magnetic-encoder-module
 *  Alternative Supplier: http://reliabuild3d.com/
 *
 *  Reilabuild encoders have been modified to improve reliability.
 */

//#define I2C_POSITION_ENCODERS
#if ENABLED(I2C_POSITION_ENCODERS)

  #define I2CPE_ENCODER_CNT         1                       // The number of encoders installed; max of 5
                                                            // encoders supported currently.

  #define I2CPE_ENC_1_ADDR          I2CPE_PRESET_ADDR_X     // I2C address of the encoder. 30-200.
  #define I2CPE_ENC_1_AXIS          X_AXIS                  // Axis the encoder module is installed on.  <X|Y|Z|E>_AXIS.
  #define I2CPE_ENC_1_TYPE          I2CPE_ENC_TYPE_LINEAR   // Type of encoder:  I2CPE_ENC_TYPE_LINEAR -or-
                                                            // I2CPE_ENC_TYPE_ROTARY.
  #define I2CPE_ENC_1_TICKS_UNIT    2048                    // 1024 for magnetic strips with 2mm poles; 2048 for
                                                            // 1mm poles. For linear encoders this is ticks / mm,
                                                            // for rotary encoders this is ticks / revolution.
  //#define I2CPE_ENC_1_TICKS_REV     (16 * 200)            // Only needed for rotary encoders; number of stepper
                                                            // steps per full revolution (motor steps/rev * microstepping)
  //#define I2CPE_ENC_1_INVERT                              // Invert the direction of axis travel.
  #define I2CPE_ENC_1_EC_METHOD     I2CPE_ECM_MICROSTEP     // Type of error error correction.
  #define I2CPE_ENC_1_EC_THRESH     0.10                    // Threshold size for error (in mm) above which the
                                                            // printer will attempt to correct the error; errors
                                                            // smaller than this are ignored to minimize effects of
                                                            // measurement noise / latency (filter).

  #define I2CPE_ENC_2_ADDR          I2CPE_PRESET_ADDR_Y     // Same as above, but for encoder 2.
  #define I2CPE_ENC_2_AXIS          Y_AXIS
  #define I2CPE_ENC_2_TYPE          I2CPE_ENC_TYPE_LINEAR
  #define I2CPE_ENC_2_TICKS_UNIT    2048
  //#define I2CPE_ENC_2_TICKS_REV   (16 * 200)
  //#define I2CPE_ENC_2_INVERT
  #define I2CPE_ENC_2_EC_METHOD     I2CPE_ECM_MICROSTEP
  #define I2CPE_ENC_2_EC_THRESH     0.10

  #define I2CPE_ENC_3_ADDR          I2CPE_PRESET_ADDR_Z     // Encoder 3.  Add additional configuration options
  #define I2CPE_ENC_3_AXIS          Z_AXIS                  // as above, or use defaults below.

  #define I2CPE_ENC_4_ADDR          I2CPE_PRESET_ADDR_E     // Encoder 4.
  #define I2CPE_ENC_4_AXIS          E_AXIS

  #define I2CPE_ENC_5_ADDR          34                      // Encoder 5.
  #define I2CPE_ENC_5_AXIS          E_AXIS

  // Default settings for encoders which are enabled, but without settings configured above.
  #define I2CPE_DEF_TYPE            I2CPE_ENC_TYPE_LINEAR
  #define I2CPE_DEF_ENC_TICKS_UNIT  2048
  #define I2CPE_DEF_TICKS_REV       (16 * 200)
  #define I2CPE_DEF_EC_METHOD       I2CPE_ECM_NONE
  #define I2CPE_DEF_EC_THRESH       0.1

  //#define I2CPE_ERR_THRESH_ABORT  100.0                   // Threshold size for error (in mm) error on any given
                                                            // axis after which the printer will abort. Comment out to
                                                            // disable abort behaviour.

  #define I2CPE_TIME_TRUSTED        10000                   // After an encoder fault, there must be no further fault
                                                            // for this amount of time (in ms) before the encoder
                                                            // is trusted again.

  /**
   * Position is checked every time a new command is executed from the buffer but during long moves,
   * this setting determines the minimum update time between checks. A value of 100 works well with
   * error rolling average when attempting to correct only for skips and not for vibration.
   */
  #define I2CPE_MIN_UPD_TIME_MS     4                       // (ms) Minimum time between encoder checks.

  // Use a rolling average to identify persistant errors that indicate skips, as opposed to vibration and noise.
  #define I2CPE_ERR_ROLLING_AVERAGE

#endif // I2C_POSITION_ENCODERS

/**
 * MAX7219 Debug Matrix
 *
 * Add support for a low-cost 8x8 LED Matrix based on the Max7219 chip as a realtime status display.
 * Requires 3 signal wires. Some useful debug options are included to demonstrate its usage.
 */
//#define MAX7219_DEBUG
#if ENABLED(MAX7219_DEBUG)
  #define MAX7219_CLK_PIN   64
  #define MAX7219_DIN_PIN   57
  #define MAX7219_LOAD_PIN  44

  //#define MAX7219_GCODE          // Add the M7219 G-code to control the LED matrix
  #define MAX7219_INIT_TEST    2   // Do a test pattern at initialization (Set to 2 for spiral)
  #define MAX7219_NUMBER_UNITS 1   // Number of Max7219 units in chain.
  #define MAX7219_ROTATE       0   // Rotate the display clockwise (in multiples of +/- 90°)
                                   // connector at:  right=0   bottom=-90  top=90  left=180
  /**
   * Sample debug features
   * If you add more debug displays, be careful to avoid conflicts!
   */
  #define MAX7219_DEBUG_PRINTER_ALIVE    // Blink corner LED of 8x8 matrix to show that the firmware is functioning
  #define MAX7219_DEBUG_PLANNER_HEAD  3  // Show the planner queue head position on this and the next LED matrix row
  #define MAX7219_DEBUG_PLANNER_TAIL  5  // Show the planner queue tail position on this and the next LED matrix row

  #define MAX7219_DEBUG_PLANNER_QUEUE 0  // Show the current planner queue depth on this and the next LED matrix row
                                         // If you experience stuttering, reboots, etc. this option can reveal how
                                         // tweaks made to the configuration are affecting the printer in real-time.
#endif  


// Enable Marlin dev mode which adds some special commands
//#define MARLIN_DEV_MODE



#endif // CONFIGURATION_ADV_H
