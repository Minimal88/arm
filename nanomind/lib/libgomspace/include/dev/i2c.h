/*
 * i2c.h
 *
 *  Created on: Aug 18, 2009
 *      Author: karl
 */

#ifndef DEV_I2C_H
#define DEV_I2C_H

#include <stdint.h>
#include <stdlib.h>

/**
 * @file
 * @brief Enables buffered communication over I2C
 * @addtogroup I2C
 *
 * @{
 */
/**
 * Maximum transfer length on I2C
 */
#define I2C_MTU 	256

/**
 * I2C device modes
 */
#define I2C_MASTER 	0
#define I2C_SLAVE 	1

/**
 * Data structure for I2C frames
 */
typedef struct __attribute__((packed)) i2c_frame_s {
	uint8_t padding;
	uint8_t retries;
	uint32_t reserved;
	uint8_t dest;
	uint8_t len_rx;
	uint16_t len;
	uint8_t data[I2C_MTU];
} i2c_frame_t;

/**
 * Initialise the I2C driver
 *
 * @param handle Which I2C bus (if more than one exists)
 * @param mode I2C device mode. Must be either I2C_MASTER or I2C_SLAVE
 * @param addr Own slave address
 * @param speed Bus speed in kbps
 * @param queue_len_tx Length of transmit queue
 * @param queue_len_rx Length of receive queue
 * @param callback If this value is set, the driver will call this function instead of using an RX queue
 */
typedef void (*i2c_callback_t) (i2c_frame_t * frame, void * pxTaskWoken);
int i2c_init(int handle, int mode, uint8_t addr, uint16_t speed, int queue_len_tx,
		int queue_len_rx, i2c_callback_t callback);

/**
 * Send I2C frame via the selected device
 *
 * @param handle Handle to the device
 * @param frame Pointer to I2C frame
 * @param timeout Ticks to wait
 * @return Error code as per error.h
 */
int i2c_send(int handle, i2c_frame_t * frame, uint16_t timeout);


/**
 * Receive I2C frame from selected device
 *
 * @param handle Handle to the device
 * @param frame Pointer to I2C frame (free this when done using csp_buffer_free!)
 * @param timeout Number of ticks to wait for a frame
 * @return Returns error code: E_NO_ERR if a frame is received, or E_TIMEOUT if timed out, E_NO_DEVICE if handle is not a valid device
 */
int i2c_receive(int handle, i2c_frame_t ** frame, uint16_t timeout);

/**
 * Excecute a I2C master write and slave read in one transaction
 *
 * @param handle Handle to the device
 * @param addr I2C address, not bit-shifted
 * @param txbuf pointer to tx data
 * @param txlen length of tx data
 * @param rxbuf pointer to rx data
 * @param rxlen length of rx data
 * @param timeout Number of ticks to wait for a frame
 * @return Returns error code: E_NO_ERR if a frame is received, or E_TIMEOUT if timed out, E_NO_DEVICE if handle is not a valid device
 */
int i2c_master_transaction(int handle, uint8_t addr, void * txbuf, size_t txlen, void * rxbuf, size_t rxlen, uint16_t timeout);


/**
 * }@
 */
#endif
