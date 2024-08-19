// ************************************ MULTIMAT_PRINT  en tarjeta ATMega 2560 ********************************************
// Este script es nuevo en Marlin. 
// Marlin.main.h  se ha creado solo para la declaracion de rutinas y constantes, llamadas y usadas por codigo nuevo de PastaPRINT 

//Las funciones que siguen, se usan  y se declaran aqui para que no de error el compilador
void gcode_G10();   
void gcode_G11();   
void gcode_M18_M84();
void gcode_G28(const bool always_home_all);  
void gcode_M0_M1();
void gcode_M117();
void gcode_M500();
void lcd_sdcard_pause();
void lcd_sdcard_resume();
void lcd_finishstatus(const bool persist=false);
void lcd_main_menu();


#if ENABLED(PASTAPRINT)
	#define  BAJAR_CAMA_ACTIVADO 	(READ(BAJAR_CAMA_PIN) == LOW)		//true =SI false= NO 
	#define  SANGRADO_MANUAL_ACTIVADO (READ(SANGRADO_MANUAL_PIN) == LOW)  	//true =SI false= NO 

	#if ENABLED(UVPRINT)
		#define  ACTIVAR_UV				WRITE(RELES_UV_PIN, LOW);	//Activa reles K4 y K5
		#define  DESACTIVAR_UV			WRITE(RELES_UV_PIN, HIGH);	
		#define  UV_ACTIVADO 			(READ(RELES_UV_PIN) == LOW)		//true =SI false= NO 
	#endif
	
	#if ENABLED(EMBOLO_TORNILLO) 
	 		#define  MORDAZA_ACCESIBLE  		(READ(FC_MORDAZA_ACCESIBLE_PIN) == LOW)  //true =SI false= NO 
			#define  LIBERAR_MORDAZA_ACTIVADO 	(READ(LIBERAR_MORDAZA_PIN) == LOW)  	//true =SI false= NO 
	#endif


	#if ENABLED(OBTU_TORN) //Modelo con tornillo y motor
		#define ESTA_OPEN  (READ(OPEN_PIN)==LOW)
		#define ESTA_HALF  (READ(HALF_PIN) == LOW)
		#define ESTA_INDEFINIDO  (READ(OPEN_PIN) == READ(HALF_PIN))
	#endif
		
	#if ENABLED(OBTU_SOLE)
		// modelo con electroiman 
		#define ESTA_OPEN  (READ(FC_OPEN_OBT_PIN)== LOW)   //TRUE= Obturador abierto 
	#endif
		
	#if ENABLED(PRESPRINT)
		#define  HAY_PRESION		(READ(PRESION_PIN) == HIGH)		//true =Hay presion   false= NO hay presion		
	#endif
	
#endif   //PASTAPRINT

//Enumeracion para G1_E_modo
enum E_modo : int {
  INICIO       = 0,
  RETRACCION   = -1,
  EXTRUSION    = 1,  
  MOVIMIENTO   = 2
};

void dwell(millis_t time);  //espera con idle()

void stop();
void gcode_M11();   //	NUEVO g_code PASTAPRINT. baja la cama.
void sonidos(unsigned char secuencia);

#if ENABLED(PASTAPRINT)
	void gcode_mod_M701();
	void limpieza();
	void gcode_G13();   //	NUEVO g_code PASTAPRINT. LIMPIEZA DE CONDUCTOS

	void recuperar();

	void sangrado_manual_extrusor(float tiempo_seg);
	void gcode_M13();   //	NUEVO g_code UVPRINT. Modifica la variable <sangrado_mm3_min>
//	void gcode_M14();   //	NUEVO g_code PASTAPRINT. Calibracion de pasos/mm extrusor
	float  gcode_time_next_move();
#endif

#if ENABLED(PRESPRINT)
	void activar_Compresor();
	void parar_Compresor();
#endif

#if ENABLED(PASTAPRINT_LIMPIEZA)
	void posicion_limpieza();
	void limpieza_inicial();
	void operar_ValvLimpieza (int nservo, int operacion);
	void activar_BombaAgua();
	void parar_BombaAgua();	
	void gcode_M12();   //	NUEVO g_code PASTAPRINT. Manejo de servos
#endif

bool stop_mensaje(const char * mesg, float tseg);
const char * tex_y_num(char * buffer, float valor, int dim, int dec);
void DEBUG_NO_REP(const char * msj, bool no_repetir);

#if ENABLED(UVPRINT)
	void reset_UVPRINT();
	void encender_UV();
	void apagar_UV();
	float gcode_time_next_move();
 	void cargar_pasta_cartucho(float pasta_mm3, float mm3_min, int direc) ;
#endif

#if ENABLED(EXTRUSOR_MIX)
    void extrusor_mix_pastaprint();
#endif


	
#if ENABLED(OBTU_TORN)
    void half_open_obturador( int valor_pwm, int direc); 
#endif

#if ENABLED(OBTU_SOLE)
void obtu_sole_voltajes();
#endif

#if ENABLED(EMBOLO_TORNILLO)
	bool posicion_actuar_mordaza(int rpm_tornillo);
	void extruir_tornillo( int8_t Modo, int pasta_mm3, float mm3_min, int direc);
	bool girar_tornillo( float rev_tornillo, int rpm_tornillo, int direc);

#endif