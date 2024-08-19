//********* !!  ojo !! hay modificaciones de PASTAPRINT !!!!!
/**
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
 * Spanish
 *
 * LCD Menu Messages
 * See also http://marlinfw.org/docs/development/lcd_language.html
 *
 */
#ifndef LANGUAGE_ES_H
#define LANGUAGE_ES_H

#define DISPLAY_CHARSET_ISO10646_1
#define NOT_EXTENDED_ISO10646_1_5X7
#define CHARSIZE 2

// textos para la LCD correspondientes a las operaciones especiales de PastaPRINT Y UVPRINT
#if ENABLED(PASTAPRINT)
	#define MSG_LIMPIEZA_INICIAL 			_UxGT("Limpieza inicial")
	#define MSG_LIMPIEZA_CICLO              _UxGT("Limpieza....Ciclo ")
	#define MSG_PASTA_CARGADA               _UxGT("Pasta cargada")
	#define MSG_CARGANDO_PASTA              _UxGT("Cargando pasta")

	#define  MSG_SUMIDEROS                  _UxGT("!SUMIDEROS!...<Click>")
	#define  MSG_TIEMPO_LIMPIEZA            _UxGT("Tiempo limpieza:") 
	#define  MSG_SECADO		                _UxGT("...Secado.... ")
	#define  MSG_ENFRIANDO	                _UxGT("...Enfriando.... ")
	#define  MSG_LIMPIEZA_FINALIZADA		_UxGT("Limpieza finalizada")
	#define  MSG_DESFOGUE                   _UxGT("Desfogue")
	#define  MSG_NO_HAY_PASTA               _UxGT("No hay pasta")
	#define  MSG_PRESOSTATO_ACTIVADO        _UxGT("!Presostato activado!")
	#define  MSG_COMPRESOR                   _UxGT("COMPRESOR")
	#define  MSG_BOMBA_AGUA                  _UxGT("BOMBA_AGUA")
	#define  MSG_VALV_DESFOGUE               _UxGT("V.DESFOGUE")
	#define  ERROR_CARGA_PASTA               _UxGT("Error. Carga pasta")
	#define  MSG_CONFIRMAR                  _UxGT("!CONFIRMAR!...<Click>")
	#define  MSG_EXTRUSIONAR_TORNILLO       _UxGT("Extrusionar")
	#define  MSG_RETRAER_TORNILLO           _UxGT("Retraer")
	#define  MSG_MONTAR_CARTUCHO		    _UxGT("Montar Ctcho")
	#define  MSG_DESMONTAR_CARTUCHO			_UxGT("Desmontar Ctcho")	
	#define  MSG_CALIBRACION				_UxGT("Calibración")
	#define  MSG_M50_CALIBRACION			_UxGT(" M50 M<mm3> S<mm3/min> N<num.tramos> I<tramo mm3/min> D<densidad>")
	#define  MSG_M51_CALIBRACION1			_UxGT(" M51 V<mm/s> C<num.capas> N<num.cuadros> H<capa> X<x0> Y<y0>")
	#define  MSG_M51_CALIBRACION2			_UxGT("\t A<LadoX> B<LadoY> I<PasoX> J<PasoY>")
	#define  MSG_EN_AVANCE					_UxGT("en avance")
	#define  MSG_EN_RETROCESO				_UxGT("en retroceso")
//	#define  MSG_FC_DESBLOQUEADO			_UxGT("FC desbloqueado")	
	#define  MSG_DIAM_EMBOLO				_UxGT("Diam.Embolo")


#endif

#if ENABLED(UVPRINT)
	#define  MSG_RESET_UVPRINT		        _UxGT("reset UVPRINT")
	#define  MSG_INIT_UVPRINT		        _UxGT("inicializa UVPRINT")
	#define  MSG_UV_ACTIVADO		        _UxGT("UV activado")
	#define  MSG_UV_APAGADO					_UxGT("UV apagado")
#endif

#if ENABLED(OBTU_SOLE)
#define MSG_PWM_MAX_OBTURADOR				_UxGT("Obt.cierre PWMmax")
#define MSG_TIME_PWM_MAX					_UxGT("Time ms PWMmax")
#define MSG_PORCPWM_MANTENIMIENTO			_UxGT("%PWMmax mantenim.")
#endif

#if ENABLED(OBTU_TORN)
#define MSG_PWM_OBTURADOR					_UxGT("Obturador PWM")
#define MSG_TIME_OPEN						_UxGT("Tiempo ms abre")
#define MSG_TIME_CLOSE						_UxGT("Tiempo ms cierra")
#define MSG_MS_OBTURADOR					_UxGT("Obt ms max")
#define MSG_MS_ENTRE_OPER_OBTURADOR			_UxGT("Obt ms <..> ope")
#endif

//#define MSG_BAJANDO_CAMA                _UxGT("Bajando... <Fin>")
#define MSG_ERROR                     	_UxGT(" >Error<")
#define  _SEG                      		_UxGT(" seg")

#define AGUA                      		_UxGT("Agua")
#define BLOQ                      		_UxGT("Bloq")
#define AIRE                      		_UxGT("Aire")


#define WELCOME_MSG                         MACHINE_NAME _UxGT(" lista.")
#define MSG_BACK                            _UxGT("Atras")
#define MSG_SD_INSERTED                     _UxGT("Tarjeta colocada")
#define MSG_SD_REMOVED                      _UxGT("Tarjeta retirada")
#define MSG_LCD_ENDSTOPS                    _UxGT("Endstops") // Max length 8 characters
#define MSG_MAIN                            _UxGT("Menu principal")
#define MSG_AUTOSTART                       _UxGT("Inicio automatico")
#define MSG_DISABLE_STEPPERS                _UxGT("Apagar motores")
#define MSG_DEBUG_MENU                      _UxGT("Menu depurar")
#define MSG_PROGRESS_BAR_TEST               _UxGT("Prueba barra avance")
#define MSG_AUTO_HOME                       _UxGT("Llevar al origen")
#define MSG_AUTO_HOME_X                     _UxGT("Origen X")
#define MSG_AUTO_HOME_Y                     _UxGT("Origen Y")
#define MSG_AUTO_HOME_Z                     _UxGT("Origen Z")
#define MSG_TMC_Z_CALIBRATION               _UxGT("Calibrar Z")
#define MSG_LEVEL_BED_HOMING                _UxGT("Origen XYZ")
#define MSG_LEVEL_BED_WAITING               _UxGT("Iniciar (Presione)")
#define MSG_LEVEL_BED_NEXT_POINT            _UxGT("Siguiente punto")
#define MSG_LEVEL_BED_DONE                  _UxGT("Nivelacion lista!")
#define MSG_SET_HOME_OFFSETS                _UxGT("Ajustar desfases")
#define MSG_HOME_OFFSETS_APPLIED            _UxGT("Desfase aplicado")
#define MSG_SET_ORIGIN                      _UxGT("Establecer origen")
#define MSG_PREHEAT_1                       _UxGT("Precal. Pasta 1")
#define MSG_PREHEAT_1_N                     MSG_PREHEAT_1 _UxGT(" ")
#define MSG_PREHEAT_1_ALL                   MSG_PREHEAT_1 _UxGT("Todo")
#define MSG_PREHEAT_1_END                   MSG_PREHEAT_1 _UxGT(" End")
#define MSG_PREHEAT_1_BEDONLY               MSG_PREHEAT_1 _UxGT("Plataforma")
#define MSG_PREHEAT_1_SETTINGS              MSG_PREHEAT_1 _UxGT("Config")
#define MSG_PREHEAT_2                       _UxGT("Precal. Pasta 2")
#define MSG_PREHEAT_2_N                     MSG_PREHEAT_2 _UxGT(" ")
#define MSG_PREHEAT_2_ALL                   MSG_PREHEAT_2 _UxGT("Todo")
#define MSG_PREHEAT_2_END                   MSG_PREHEAT_2 _UxGT(" End")
#define MSG_PREHEAT_2_BEDONLY               MSG_PREHEAT_2 _UxGT("Plataforma")
#define MSG_PREHEAT_2_SETTINGS              MSG_PREHEAT_2 _UxGT("Config")
#define MSG_COOLDOWN                        _UxGT("Enfriar")
#define MSG_SWITCH_PS_ON                    _UxGT("Encender")
#define MSG_SWITCH_PS_OFF                   _UxGT("Apagar")
#define MSG_EXTRUDE                         _UxGT("Extruir")
#define MSG_RETRACT                         _UxGT("Retraer")
#define MSG_MOVE_AXIS                       _UxGT("Mover ejes")
#define MSG_BED_LEVELING                    _UxGT("Nivelar plataforma")
#define MSG_LEVEL_BED                       _UxGT("Nivelar plataforma")
#define MSG_MOVING                          _UxGT("Moviendo...")
#define MSG_FREE_XY                         _UxGT("Libre XY")
#define MSG_MOVE_X                          _UxGT("Mover X")
#define MSG_MOVE_Y                          _UxGT("Mover Y")
#define MSG_MOVE_Z                          _UxGT("Mover Z")
#define MSG_MOVE_E                          _UxGT("Extrusor")
#define MSG_MOVE_01MM                       _UxGT("Mover 0.1mm")
#define MSG_MOVE_1MM                        _UxGT("Mover 1mm")
#define MSG_MOVE_10MM                       _UxGT("Mover 10mm")
#define MSG_SPEED                           _UxGT("Velocidad")
#define MSG_BED_Z                           _UxGT("Plataforma Z")
#define MSG_NOZZLE                          _UxGT("Boquilla")
#define MSG_BED                             _UxGT("Plataforma")
#define MSG_FAN_SPEED                       _UxGT("Ventilador")
#define MSG_FLOW                            _UxGT("Flujo")
#define MSG_CONTROL                         _UxGT("Control")
#define MSG_MIN                             _UxGT(" ") LCD_STR_THERMOMETER _UxGT(" Min")
#define MSG_MAX                             _UxGT(" ") LCD_STR_THERMOMETER _UxGT(" Max")
#define MSG_FACTOR                          _UxGT(" ") LCD_STR_THERMOMETER _UxGT(" Fact")
#define MSG_AUTOTEMP                        _UxGT("Temperatura Auto.")
#define MSG_ON                              _UxGT(" SI")
#define MSG_OFF                             _UxGT(" N0")
#define MSG_PID_P                           _UxGT("PID-P")
#define MSG_PID_I                           _UxGT("PID-I")
#define MSG_PID_D                           _UxGT("PID-D")
#define MSG_PID_C                           _UxGT("PID-C")
#define MSG_SELECT                          _UxGT("Seleccionar")
#define MSG_ACC                             _UxGT("Aceleracion")
#define MSG_JERK                            _UxGT("Jerk")
#if IS_SCARA
  #define MSG_VA_JERK                       _UxGT("Va-jerk")
  #define MSG_VB_JERK                       _UxGT("Vb-jerk")
  #define MSG_VC_JERK                       _UxGT("Vz-jerk")
#elif IS_DELTA
  #define MSG_VA_JERK                       _UxGT("Va-jerk")
  #define MSG_VB_JERK                       _UxGT("Vb-jerk")
  #define MSG_VC_JERK                       _UxGT("Vc-jerk")
#else
  #define MSG_VA_JERK                       _UxGT("Vx-jerk")
  #define MSG_VB_JERK                       _UxGT("Vy-jerk")
  #define MSG_VC_JERK                       _UxGT("Vz-jerk")
#endif
#define MSG_VE_JERK                         _UxGT("Ve-jerk")
#define MSG_VMAX                            _UxGT("Vmax")
#define MSG_VMIN                            _UxGT("Vmin")
#define MSG_VTRAV_MIN                       _UxGT("Vel. viaje min")
#define MSG_ACCELERATION                    MSG_ACC
#define MSG_AMAX                            _UxGT("Acel. max")
#define MSG_A_RETRACT                       _UxGT("Acel. retrac.")
#define MSG_A_TRAVEL                        _UxGT("Acel. Viaje")
#define MSG_STEPS_PER_MM                    _UxGT("Pasos/mm")


#if IS_SCARA
  #define MSG_ASTEPS                        _UxGT("A pasos/deg")
  #define MSG_BSTEPS                        _UxGT("B pasos/deg")
  #define MSG_CSTEPS                        _UxGT("C pasos/mm")
#elif IS_DELTA
  #define MSG_ASTEPS                        _UxGT("A pasos/mm")
  #define MSG_BSTEPS                        _UxGT("B pasos/mm")
  #define MSG_CSTEPS                        _UxGT("C pasos/mm")
#else
  #define MSG_ASTEPS                        _UxGT("X pasos/mm")
  #define MSG_BSTEPS                        _UxGT("Y pasos/mm")
  #define MSG_CSTEPS                        _UxGT("Z pasos/mm")
#endif
#define MSG_ESTEPS                          _UxGT("E pasos/mm")
#define MSG_E1STEPS                         _UxGT("E1 pasos/mm")
/*
#define MSG_E2STEPS                         _UxGT("E2 pasos/mm")
#define MSG_E3STEPS                         _UxGT("E3 pasos/mm")
#define MSG_E4STEPS                         _UxGT("E4 pasos/mm")
#define MSG_E5STEPS                         _UxGT("E5 pasos/mm")
*/

#define  MSG_CARTUCHO_MM3_MOVE_MINIMUM 		_UxGT("Carga mínima (mm3)=") // Minimo numero de mm3 para efectuar el movimiento del tornillo.											
#define  MSG_CARTUCHO_MM3_MIN			  	_UxGT("Mínimo/Maximo (mm3/min)=")	// Velocidad en mm3/minuto minimo admisible para efectuar movimiento del tornillo.											
	
#define MSG_PASOS_MM3                       _UxGT("Pasos/mm3")
#define MSG_TEMPERATURE                     _UxGT("Temperatura")
#define MSG_MOTION                          _UxGT("Movimiento")
#define MSG_FILAMENT                        _UxGT("Boquilla")
#define MSG_VOLUMETRIC_ENABLED              _UxGT("E volumetric mm3")
#define MSG_PORC_RENDMTO_EXTRUSION 			_UxGT("% Rend.Extrusor")

#define MSG_ADVANCE_K                       _UxGT("Avance K")
#define MSG_CONTRAST                        _UxGT("Contraste")
#define MSG_STORE_EEPROM                    _UxGT("Guardar memoria")
#define MSG_LOAD_EEPROM                     _UxGT("Cargar memoria")
#define MSG_RESTORE_FAILSAFE                _UxGT("Restaurar memoria")
#define MSG_REFRESH                         _UxGT("Volver a cargar")
#define MSG_WATCH                           _UxGT("Informacion")
#define MSG_PREPARE                         _UxGT("Preparar")
#define MSG_TUNE                            _UxGT("Ajustar")
#define MSG_PAUSE_PRINT                     _UxGT("Pausar impresion")
#define MSG_RESUME_PRINT                    _UxGT("Reanudar impresion")
#define MSG_STOP_PRINT                      _UxGT("Detener impresion")
#define MSG_CARD_MENU                       _UxGT("Menu de SD")
#define MSG_NO_CARD                         _UxGT("No hay tarjeta SD")
#define MSG_DWELL                           _UxGT("Reposo...")
#define MSG_USERWAIT                        _UxGT("Esperando ordenes")
#define MSG_PRINT_ABORTED                   _UxGT("Impresion cancelada")
#define MSG_NO_MOVE                         _UxGT("Sin movimiento")
#define MSG_KILLED                          _UxGT("Parada de emergencia")
#define MSG_STOPPED                         _UxGT("Detenida")
#define MSG_CONTROL_RETRACT                 _UxGT("Retraer mm")
#define MSG_CONTROL_RETRACT_SWAP            _UxGT("Interc. Retraer mm")
#define MSG_CONTROL_RETRACTF                _UxGT("Retraer  V")
#define MSG_CONTROL_RETRACT_ZLIFT           _UxGT("Levantar mm")
#define MSG_CONTROL_RETRACT_RECOVER         _UxGT("DesRet mm")
#define MSG_CONTROL_RETRACT_RECOVER_SWAP    _UxGT("Interc. DesRet mm")
#define MSG_CONTROL_RETRACT_RECOVERF        _UxGT("DesRet V")
#define MSG_AUTORETRACT                     _UxGT("Retraccion Auto.")
#define MSG_FILAMENTCHANGE                  _UxGT("Cambiar filamento")
#define MSG_INIT_SDCARD                     _UxGT("Iniciando tarjeta")
#define MSG_CNG_SDCARD                      _UxGT("Cambiar tarjeta")
#define MSG_ZPROBE_OUT                      _UxGT("Sonda Z fuera")
#define MSG_BLTOUCH_SELFTEST                _UxGT("BLTouch Auto-Prueba")
#define MSG_BLTOUCH_RESET                   _UxGT("Reiniciar BLTouch")
#define MSG_HOME                            _UxGT("Home")  // Used as MSG_HOME " " MSG_X MSG_Y MSG_Z " " MSG_FIRST
#define MSG_FIRST                           _UxGT("inic.")
#define MSG_ZPROBE_ZOFFSET                  _UxGT("Desfase Z")
#define MSG_BABYSTEP_X                      _UxGT("Micropaso X")
#define MSG_BABYSTEP_Y                      _UxGT("Micropaso Y")
#define MSG_BABYSTEP_Z                      _UxGT("Micropaso Z")
#define MSG_ENDSTOP_ABORT                   _UxGT("Cancelado - Endstop")
#define MSG_HEATING_FAILED_LCD              _UxGT("Error: al calentar")
#define MSG_ERR_REDUNDANT_TEMP              _UxGT("Error: temperatura")
#define MSG_THERMAL_RUNAWAY                 _UxGT("Error: temperatura")
#define MSG_ERR_MAXTEMP                     _UxGT("Error: Temp Maxima")
#define MSG_ERR_MINTEMP                     _UxGT("Error: Temp Minima")
#define MSG_ERR_MAXTEMP_BED                 _UxGT("Error: Temp Max Plat")
#define MSG_ERR_MINTEMP_BED                 _UxGT("Error: Temp Min Plat")
#define MSG_ERR_Z_HOMING                    MSG_HOME _UxGT(" ") MSG_X MSG_Y _UxGT(" ") MSG_FIRST
#define MSG_HALTED                          _UxGT("IMPRESORA PARADA")
#define MSG_PLEASE_RESET                    _UxGT("Por favor, reinicie")
#define MSG_SHORT_DAY                       _UxGT("d") 			// One character only
#define MSG_SHORT_HOUR                      _UxGT("h") 			// One character only
#define MSG_SHORT_MINUTE                    _UxGT("m")		 // One character only
#define MSG_HEATING                         _UxGT("Calentando...")
#define MSG_BED_HEATING                     _UxGT("Calentando Plat...")
#define MSG_DELTA_CALIBRATE                 _UxGT("Calibracion Delta")
#define MSG_DELTA_CALIBRATE_X               _UxGT("Calibrar X")
#define MSG_DELTA_CALIBRATE_Y               _UxGT("Calibrar Y")
#define MSG_DELTA_CALIBRATE_Z               _UxGT("Calibrar Z")
#define MSG_DELTA_CALIBRATE_CENTER          _UxGT("Calibrar Centro")
#define MSG_DELTA_AUTO_CALIBRATE            _UxGT("Auto Calibracion")
#define MSG_DELTA_HEIGHT_CALIBRATE          _UxGT("Est. Altura Delta")
#define MSG_INFO_MENU                       _UxGT("Inf. Impresora")
#define MSG_INFO_PRINTER_MENU               _UxGT("Inf. Impresora")
#define MSG_INFO_STATS_MENU                 _UxGT("Estadisticas Imp.")
#define MSG_INFO_BOARD_MENU                 _UxGT("Inf. Controlador")
#define MSG_INFO_THERMISTOR_MENU            _UxGT("Termistores")
#define MSG_INFO_EXTRUDERS                  _UxGT("Extrusores")
#define MSG_INFO_BAUDRATE                   _UxGT("Baudios")
#define MSG_INFO_PROTOCOL                   _UxGT("Protocolo")
#define MSG_CASE_LIGHT                      _UxGT("Luz cabina")

#if LCD_WIDTH > 19
  #define MSG_INFO_PRINT_COUNT              _UxGT("Conteo de impresion")
  #define MSG_INFO_COMPLETED_PRINTS         _UxGT("Completadas")
  #define MSG_INFO_PRINT_TIME               _UxGT("Tiempo total de imp.")
  #define MSG_INFO_PRINT_LONGEST            _UxGT("Impresion mas larga")
  #define MSG_INFO_PRINT_FILAMENT           _UxGT("Total de Extrusion")
#else
  #define MSG_INFO_PRINT_COUNT              _UxGT("Impresiones")
  #define MSG_INFO_COMPLETED_PRINTS         _UxGT("Completadas")
  #define MSG_INFO_PRINT_TIME               _UxGT("Total")
  #define MSG_INFO_PRINT_LONGEST            _UxGT("Mas larga")
  #define MSG_INFO_PRINT_FILAMENT           _UxGT("Extrusion")
#endif

#define MSG_INFO_MIN_TEMP                   _UxGT("Temperatura minima")
#define MSG_INFO_MAX_TEMP                   _UxGT("Temperatura maxima")
#define MSG_INFO_PSU                        _UxGT("Fuente de poder")
#define MSG_DRIVE_STRENGTH                  _UxGT("Potencia driver")
#define MSG_DAC_PERCENT                     _UxGT("Driver %")
#define MSG_DAC_EEPROM_WRITE                _UxGT("Escribe DAC EEPROM")

/*     PARA GANAR ESPACIO SE ELIMINAN ESTOS MENSAJES QUE NO TIENEN USO PARA PASTAPRINT

#define MSG_FILAMENT_CHANGE_HEADER_PAUSE    _UxGT("IMPR. PAUSADA")
#define MSG_FILAMENT_CHANGE_OPTION_HEADER   _UxGT("OPC. REINICIO:")
#define MSG_FILAMENT_CHANGE_OPTION_RESUME   _UxGT("Resumir imp.")

#define MSG_FILAMENT_CHANGE_NOZZLE          _UxGT("  Boquilla: ")

#define MSG_FILAMENT_CHANGE_INIT_1          _UxGT("Esperando para")

#define MSG_FILAMENT_CHANGE_INSERT_1        _UxGT("Inserte el filamento")
#define MSG_FILAMENT_CHANGE_INSERT_2        _UxGT("y presione el boton")

#if LCD_HEIGHT >= 4
  // Up to 3 lines allowed
  #define MSG_FILAMENT_CHANGE_INIT_2        _UxGT("iniciar cambio")
  #define MSG_FILAMENT_CHANGE_INIT_3        _UxGT("de filamento")
  #define MSG_FILAMENT_CHANGE_INSERT_3      _UxGT("para continuar...")
#else // LCD_HEIGHT < 4
  // Up to 2 lines allowed
  #define MSG_FILAMENT_CHANGE_INIT_2        _UxGT("iniciar cambio fil.")
#endif // LCD_HEIGHT < 4

#define MSG_FILAMENT_CHANGE_UNLOAD_1        _UxGT("Esperando para")
#define MSG_FILAMENT_CHANGE_UNLOAD_2        _UxGT("expulsar filamento")
#define MSG_FILAMENT_CHANGE_LOAD_1          _UxGT("Esperado para")
#define MSG_FILAMENT_CHANGE_LOAD_2          _UxGT("cargar el filamento")
#define MSG_FILAMENT_CHANGE_RESUME_1        _UxGT("Esperando imp.")
#define MSG_FILAMENT_CHANGE_RESUME_2        _UxGT("para resumir")
#define MSG_FILAMENT_CHANGE_HEAT_1          _UxGT("Oprima boton para")
#define MSG_FILAMENT_CHANGE_HEAT_2          _UxGT("Calentar la boquilla")
#define MSG_FILAMENT_CHANGE_HEATING_1       _UxGT("Calentando boquilla")
#define MSG_FILAMENT_CHANGE_HEATING_2       _UxGT("Espere por favor")
*/

#endif // LANGUAGE_ES_H
