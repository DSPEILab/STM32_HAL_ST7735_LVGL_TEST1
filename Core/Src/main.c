/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <lvgl.h>
#include "lv_port_disp.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
static void lv_ex_label_1(void)
{
    lv_obj_t * label2 = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_recolor(label2, true);
    lv_label_set_long_mode(label2, LV_LABEL_LONG_SROLL_CIRC); /*Circular scroll*/
    lv_obj_set_width(label2, 100);
    // Hello world ! Trisuborn.
    lv_label_set_text(label2, "#ff0000 Hello# #00ff00 world ! Trisuborn.#");
    lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 0);
}
void lvgl_button_style_test(void)
{
    static lv_anim_path_t path_overshoot;
    lv_anim_path_init(&path_overshoot);
    lv_anim_path_set_cb(&path_overshoot, lv_anim_path_overshoot);
 
    static lv_anim_path_t path_ease_out;
    lv_anim_path_init(&path_ease_out);
    lv_anim_path_set_cb(&path_ease_out, lv_anim_path_ease_out);
 
    static lv_anim_path_t path_ease_in_out;
    lv_anim_path_init(&path_ease_in_out);
    lv_anim_path_set_cb(&path_ease_in_out, lv_anim_path_ease_in_out);
 
    /*Gum-like button*/
    static lv_style_t style_gum;
    lv_style_init(&style_gum);
    lv_style_set_transform_width(&style_gum, LV_STATE_PRESSED, 10);
    lv_style_set_transform_height(&style_gum, LV_STATE_PRESSED, -10);
    lv_style_set_value_letter_space(&style_gum, LV_STATE_PRESSED, 5);
    lv_style_set_transition_path(&style_gum, LV_STATE_DEFAULT, &path_overshoot);
    lv_style_set_transition_path(&style_gum, LV_STATE_PRESSED, &path_ease_in_out);
    lv_style_set_transition_time(&style_gum, LV_STATE_DEFAULT, 250);
    lv_style_set_transition_delay(&style_gum, LV_STATE_DEFAULT, 100);
    lv_style_set_transition_prop_1(&style_gum, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_WIDTH);
    lv_style_set_transition_prop_2(&style_gum, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_HEIGHT);
    lv_style_set_transition_prop_3(&style_gum, LV_STATE_DEFAULT, LV_STYLE_VALUE_LETTER_SPACE);
 
    lv_obj_t* btn1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, -80);
    lv_obj_add_style(btn1, LV_BTN_PART_MAIN, &style_gum);
 
    /*Instead of creating a label add a values string*/
    lv_obj_set_style_local_value_str(btn1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, "Gum");
 
    /*Halo on press*/
    static lv_style_t style_halo;
    lv_style_init(&style_halo);
    lv_style_set_transition_time(&style_halo, LV_STATE_PRESSED, 400);
    lv_style_set_transition_time(&style_halo, LV_STATE_DEFAULT, 0);
    lv_style_set_transition_delay(&style_halo, LV_STATE_DEFAULT, 200);
    lv_style_set_outline_width(&style_halo, LV_STATE_DEFAULT, 0);
    lv_style_set_outline_width(&style_halo, LV_STATE_PRESSED, 20);
    lv_style_set_outline_opa(&style_halo, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_outline_opa(&style_halo, LV_STATE_FOCUSED, LV_OPA_COVER);   /*Just to be sure, the theme might use it*/
    lv_style_set_outline_opa(&style_halo, LV_STATE_PRESSED, LV_OPA_TRANSP);
    lv_style_set_transition_prop_1(&style_halo, LV_STATE_DEFAULT, LV_STYLE_OUTLINE_OPA);
    lv_style_set_transition_prop_2(&style_halo, LV_STATE_DEFAULT, LV_STYLE_OUTLINE_WIDTH);
 
    lv_obj_t* btn2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_style(btn2, LV_BTN_PART_MAIN, &style_halo);
    lv_obj_set_style_local_value_str(btn2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, "Halo");
 
    /*Ripple on press*/
    static lv_style_t style_ripple;
    lv_style_init(&style_ripple);
    lv_style_set_transition_time(&style_ripple, LV_STATE_PRESSED, 300);
    lv_style_set_transition_time(&style_ripple, LV_STATE_DEFAULT, 0);
    lv_style_set_transition_delay(&style_ripple, LV_STATE_DEFAULT, 300);
    lv_style_set_bg_opa(&style_ripple, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_opa(&style_ripple, LV_STATE_PRESSED, LV_OPA_80);
    lv_style_set_border_width(&style_ripple, LV_STATE_DEFAULT, 0);
    lv_style_set_outline_width(&style_ripple, LV_STATE_DEFAULT, 0);
    lv_style_set_transform_width(&style_ripple, LV_STATE_DEFAULT, -20);
    lv_style_set_transform_height(&style_ripple, LV_STATE_DEFAULT, -20);
    lv_style_set_transform_width(&style_ripple, LV_STATE_PRESSED, 0);
    lv_style_set_transform_height(&style_ripple, LV_STATE_PRESSED, 0);
 
    lv_style_set_transition_path(&style_ripple, LV_STATE_DEFAULT, &path_ease_out);
    lv_style_set_transition_prop_1(&style_ripple, LV_STATE_DEFAULT, LV_STYLE_BG_OPA);
    lv_style_set_transition_prop_2(&style_ripple, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_WIDTH);
    lv_style_set_transition_prop_3(&style_ripple, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_HEIGHT);
 
    lv_obj_t* btn3 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_align(btn3, NULL, LV_ALIGN_CENTER, 0, 80);
    lv_obj_add_style(btn3, LV_BTN_PART_MAIN, &style_ripple);
    lv_obj_set_style_local_value_str(btn3, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, "Ripple");
}
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI5_Init();
  MX_TIM10_Init();
  /* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(GPIOA,LED3_Pin,GPIO_PIN_RESET);
	LCD_Init(2, 1); 
	LCD_Rect_Fill(0, 0, 160, 128, BLACK);
	//LCD_Init();
	//LCD_Clear(CYAN);
	lv_init();
	lv_port_disp_init(); 
	lv_ex_label_1();
	//lvgl_button_style_test();
	HAL_GPIO_WritePin(GPIOA,LED3_Pin,GPIO_PIN_SET);
	HAL_TIM_Base_Start_IT(&htim10);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		//lv_tick_inc(1);
		lv_task_handler();
		HAL_Delay(1);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 200;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
 if(htim == (&htim10))
 {
	lv_tick_inc(1);
	//HAL_GPIO_TogglePin(GPIOA,LED2_Pin);
 }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
		HAL_Delay(500);
		HAL_GPIO_TogglePin(GPIOA,LED1_Pin);
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
