#include <aide.h>

static lv_obj_t * chiffre0;
static lv_obj_t * chiffre1;
static lv_obj_t * chiffre2;
static lv_obj_t * indice;

LV_IMG_DECLARE(n0);
LV_IMG_DECLARE(n1);
LV_IMG_DECLARE(n2);
LV_IMG_DECLARE(n3);
LV_IMG_DECLARE(n4);
LV_IMG_DECLARE(n5);
LV_IMG_DECLARE(n6);
LV_IMG_DECLARE(n7);
LV_IMG_DECLARE(n8);
LV_IMG_DECLARE(n9);

extern UART_HandleTypeDef huart6;
extern UART_HandleTypeDef huart1;
extern uint8_t pData[5];
extern uint8_t Tab[3];

void score()
{
	HAL_UART_Receive_IT(&huart6, pData, 4);
	HAL_UART_Receive_IT(&huart1, pData, 4);
	lv_obj_t * panel1 = lv_obj_create(lv_scr_act());
    lv_obj_set_height(panel1, LV_SIZE_CONTENT);
    lv_obj_align(panel1, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_size(panel1, 480, 272);

    lv_obj_clear_flag(panel1, LV_OBJ_FLAG_SCROLLABLE); // Permet de rendre l'objet non défilable
    lv_obj_set_scrollbar_mode(panel1, LV_SCROLLBAR_MODE_OFF); // Permet de retirer les scrollbar

    chiffre0 = lv_img_create(panel1);
    chiffre1 = lv_img_create(panel1);
    chiffre2 = lv_img_create(panel1);

    lv_img_set_src(chiffre0, &n0);
    lv_img_set_src(chiffre1, &n0);
    lv_img_set_src(chiffre2, &n0);

    static lv_coord_t grid_col_dsc[] = {150, 150, 150, LV_GRID_TEMPLATE_LAST};
    static lv_coord_t grid_row_dsc[] = {260, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(panel1, grid_col_dsc, grid_row_dsc);

    lv_obj_set_grid_cell(chiffre0, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(chiffre1, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(chiffre2, LV_GRID_ALIGN_START, 2, 1, LV_GRID_ALIGN_CENTER, 0, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	int mes = 0;
	int i;
	HAL_UART_Transmit(&huart1, pData, sizeof(pData), HAL_MAX_DELAY);
	if(pData[0] == '0')
	{
		for(i=2; i>=0;i--)
		{
			mes = Tab[i] - pData[i+1];
			if(mes < 0)
			{
				Tab[i] = mes + 58;
				Tab[i-1] = Tab[i-1] - 1;
			}
			else
			{
				Tab[i] = mes + 48;
			}
		}
	}
	else
	{
		for(i=2; i>=0;i--)
		{
			mes = Tab[i] + pData[i+1];
			if(mes >= 106)
			{
				Tab[i] = mes - 58;
				Tab[i-1] = Tab[i-1] + 1;
			}
			else
			{
				Tab[i] = mes - 48;
			}
		}
	}

	for(i=0; i<3;i++)
	{
		if(Tab[i] < '0')
		{
			Tab[i] = '0';
		}
		else if(Tab[i] > '9')
		{
			Tab[i] = '9';
		}
	}

	for(int i=0;i<3; i++)
	{
		if(i == 0)
		{
			indice = chiffre0;
		}
		else if(i == 1)
		{
			indice = chiffre1;
		}
		else if(i == 2)
		{
			indice = chiffre2;
		}

	    	    	switch(Tab[i])
	    	    	{
	    	    	case '0':
	    	    		lv_img_set_src(indice, &n0);
	    	    		break;
	    	    	case '1':
	    	    		lv_img_set_src(indice, &n1);
	    	    		break;
	    	    	case '2':
	    	    		lv_img_set_src(indice, &n2);
	    	    		break;
	    	    	case '3':
	    	    		lv_img_set_src(indice, &n3);
	    	    		break;
	    	    	case '4':
	    	    		lv_img_set_src(indice, &n4);
	    	    		break;
	    	    	case '5':
	    	    	   	lv_img_set_src(indice, &n5);
	    	    	   	break;
	    	    	case '6':
	    	    	    lv_img_set_src(indice, &n6);
	    	    	    break;
	    	    	case '7':
	    	    	    lv_img_set_src(indice, &n7);
	    	    	    break;
	    	    	case '8':
	    	    	    lv_img_set_src(indice, &n8);
	    	    	    break;
	    	    	case '9':
	    	    	    lv_img_set_src(indice, &n9);
	    	    	    break;
	    	    	default:
	    	    		lv_img_set_src(indice, &n0);
	    	    		break;
	    	    	}
	}
}
