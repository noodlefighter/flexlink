/**
 * @file
 * @brief 
 */

#ifndef FLEXLINK_H_
#define FLEXLINK_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct flexlink_frame {
    uint8_t addr;
    uint8_t cmd;
    uint16_t crc16;     /**< @brief CRC16_CCITT */
} flexlink_frame_t;

struct flexlink_master_cfg {
    int (*pfn_write) (const uint8_t *p_dat, int dat_len);
    int (*pfn_read) (uint8_t *p_buf);
    bool (*pfn_pin_s_is_active) (void);
};

struct flexlink_slave_cfg {
    int (*pfn_write) (const uint8_t *p_dat, int dat_len);
    void (*pfn_set_pin_s) (bool active);
    bool (*pfn_pin_s_is_active) (void);
};

typedef struct {
    const struct flexlink_master_cfg *p_cfg;
} flexlink_master_t;

typedef struct {
    const struct flexlink_slave_cfg *p_cfg;
} flexlink_slave_t;

#ifdef __cplusplus
extern "C"
{
#endif

int flexlink_master_init (flexlink_master_t *p_obj, const struct flexlink_master_cfg *p_cfg);
int flexlink_master_loop (flexlink_master_t *p_obj);

int flexlink_slave_init (flexlink_slave_t *p_obj, const struct flexlink_slave_cfg *p_cfg);
int flexlink_slave_data_received (flexlink_slave_t *p_obj, const uint8_t *p_dat, int dat_len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FLEXLINK_H_ */
