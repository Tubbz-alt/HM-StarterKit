/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :2017/6/27	                                       */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :RX631 48P                                             */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
//#include "typedefine.h"
#include "iodefine.h"
#include "mathf.h"
#include "sci.h"
#include "init.h"
#include "spi.h"
#include "i2c.h"
#include "parameters.h"
#include "glob_var.h"
#include "run.h"
#include "interface.h"
#include "DataFlash.h"
#include "portdef.h"
#include "fast.h"
#include "search.h"

extern void wait_ms(int wtime);

void adjust(void)
{

	int i = 0;
	int flash_time = 0;
	char flash;
	short ad_mode = 1;
	while(1){
		switch(ad_mode){

			
			case 1:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	O	X	X	X	*
				*					*
				*****************************************/
				
				//�Z���T�[�̑O�Ɏ���������ăX�^�[�g
				if(sen_fr.value + sen_fl.value + sen_r.value + sen_l.value > SEN_DECISION * 4){
					BEEP();
					//�ǐ����L���ɂ���
					con_wall.enable = true;
					while(1){
						//A/D sensor
						SCI_printf("sen_r.value: %d\n\r",sen_r.value);
						SCI_printf("sen_l.value: %d\n\r",sen_l.value);
						SCI_printf("sen_fr.value: %d\n\r",sen_fr.value);
						SCI_printf("sen_fl.value: %d\n\r",sen_fl.value);
						SCI_printf("V_bat: %d\n\r",(int)(V_bat*1000));
						SCI_printf("sen_r.th_wall: %d\n\r",sen_r.th_wall);
						SCI_printf("sen_l.th_wall: %d\n\r",sen_l.th_wall);
						SCI_printf("sen_fr.th_wall: %d\n\r",sen_fr.th_wall);
						SCI_printf("sen_fl.th_wall: %d\n\r",sen_fl.th_wall);
						SCI_printf("con_wall.omega: %d\n\r",(int)(con_wall.omega*1000));
						SCI_printf("speed_r: %d\n\r", (int)(speed_r*100));
						SCI_printf("speed_l: %d\n\r", (int)(speed_l*100));
						//gyro
						SCI_printf("degree: %d\n\r",(int)degree*10);;			
						SCI_printf("gyro: %d\n\r", (int)(ang_vel*1000) );
						//encoder
						SCI_printf("locate_r: %d\n\r",locate_r);
						SCI_printf("locate_l: %d\n\r",locate_l);	
					
						//switch
						SCI_printf("switchC: %d\n\r",SW_C);
						SCI_printf("switchU: %d\n\r",SW_U);
						SCI_printf("switchD: %d\n\r",SW_D);
						wait_ms(100);
						//��ʃN���A�V�[�P���X
						SCI_printf("\x1b[2J");				//�N���A�X�N���[��[CLS]
						SCI_printf("\x1b[0;0H");			//�J�[�\����0,0�Ɉړ�
						
						//�v�b�V���X�C�b�`�p����
						push_switch = IOex_SWITCH();
			
						if(SW_C == 1){
							BEEP();
							break;	
						}
					}
				}
				
				break;
				
			case 2:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	X	O	X	X	*
				*					*
				*****************************************/	
			
				//�Z���T�[�̑O�Ɏ���������ăX�^�[�g
				if(sen_fr.value + sen_fl.value + sen_r.value + sen_l.value > SEN_DECISION * 4){
					BEEP();
					gyro_get_ref();
					BEEP();
					log_flag = 1;
					log_timer = 0;
					straight(SECTION,SEARCH_ACCEL,SEARCH_SPEED,0);
					log_flag = 0;
					MOT_POWER_OFF;
					BEEP();
					wait_ms(500);
				}
				
				break;
				
			case 3:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	O	O	X	X	*
				*					*
				*****************************************/
				//�}�b�v�̕\��
				//�Z���T�[�̑O�Ɏ���������ăX�^�[�g
				if(sen_fr.value + sen_fl.value + sen_r.value + sen_l.value > SEN_DECISION * 4){
					BEEP();
					gyro_get_ref();
					BEEP();
					log_flag = 1;
					log_timer = 0;
					turn(90,TURN_ACCEL,TURN_SPEED,RIGHT);
					log_flag = 0;
					MOT_POWER_OFF;
					BEEP();
					wait_ms(500);
				}
				
				break;
				
			case 4:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	X	X	O	X	*
				*					*
				*****************************************/
			
				//�Z���T�[�̑O�Ɏ���������ăX�^�[�g
				if(sen_fr.value + sen_fl.value + sen_r.value + sen_l.value > SEN_DECISION * 4){
					BEEP();

					wait_ms(500);
				}
				
				break;
				
			case 5:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	O	X	O	X	*
				*					*
				*****************************************/
			
				//�Z���T�[�̑O�Ɏ���������ăX�^�[�g
				if(sen_fr.value + sen_fl.value + sen_r.value + sen_l.value > SEN_DECISION * 4){
					BEEP();

					wait_ms(500);		
				}
				
				break;
				
			case 6:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	X	O	O	X	*
				*					*
				*****************************************/
				//�}�b�v�\��
				//�Z���T�[�̑O�Ɏ���������ăX�^�[�g
				if(sen_fr.value + sen_fl.value + sen_r.value + sen_l.value > SEN_DECISION * 4){
					BEEP();
					map_copy();
					map_view();
					wait_ms(500);	
				}
				
				break;
				
			case 7:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	O	O	O	X	*
				*					*
				*****************************************/
				//���O�o��
				//�Z���T�[�̑O�Ɏ���������ăX�^�[�g
				if(sen_fr.value + sen_fl.value + sen_r.value + sen_l.value > SEN_DECISION * 4){
					BEEP();
					SCI_printf("time[msec],len_mouse[mm],tar_speed[mm/s],speed[mm/s],Duty_R[%],Duty_L[%],V_battery[mV],tar_degree[deg],degree[deg],tar_ang_vel[rad/s],ang_vel[rad/s],I_tar_ang_vel[rad],I_ang_vel[rad],ang_acc[rad/ss]\n\r");
					for(i = 0; i < LOG_CNT; i++){
						
						SCI_printf("%d,",i);//time[msec]
						SCI_printf("%d,",log[0][i]);
						SCI_printf("%d,",log[1][i]);
						SCI_printf("%d,",log[2][i]);
						SCI_printf("%d,",log[3][i]);
						SCI_printf("%d,",log[4][i]);
						SCI_printf("%d,",log[5][i]);
						SCI_printf("%d,",log[6][i]);
						SCI_printf("%d,",log[7][i]);
						SCI_printf("%d,",log[8][i]);
						SCI_printf("%d,",log[9][i]);
						SCI_printf("%d,",log[10][i]);
						SCI_printf("%d\n\r",log[11][i]);		
					}
					wait_ms(500);	
				}				
				break;
			//mode0~7�ȊO�̏ꍇ�B�������Ȃ��B
			default:
				break;
			
		}
		
		//���[�h�؂�ւ��p����
		if(speed > 0.1){
			if(ad_mode == 7){
				ad_mode = 1;
			}else{
				ad_mode ++;
			}
			for(i = 0; i < 100*1000*10; i++);
			BEEP();
		}
		
		if(speed < -0.1){
			if(ad_mode == 1){
				ad_mode = 7;
			}else{
				ad_mode --;
		}
			for(i = 0; i < 100*1000*10; i++);
			BEEP(); 
		}
		if(flash_time > 0x00FF){
			flash_time = 0;
			if(flash == 0x08){
				flash = 0x00;
			}else{
				flash = 0x08;
			}
		}
			
		flash_time++;
		LED(ad_mode | flash);
		
		//�v�b�V���X�C�b�`�p����
		push_switch = IOex_SWITCH();
		MOT_POWER_OFF;
		
		if(SW_C == 1){
			BEEP();
			break;	
		}
	}
}
