#include "base/security.h"

#define SEC_PARAM_TIMEOUT               30                                          /**< Timeout for Pairing Request or Security Request (in seconds). */
#define SEC_PARAM_BOND                  1                                           /**< Perform bonding. */
#define SEC_PARAM_MITM                  0                                           /**< Man In The Middle protection not required. */
#define SEC_PARAM_IO_CAPABILITIES       BLE_GAP_IO_CAPS_NONE                        /**< No I/O capabilities. */
#define SEC_PARAM_OOB                   0                                           /**< Out Of Band data not available. */
#define SEC_PARAM_MIN_KEY_SIZE          7                                           /**< Minimum encryption key size. */
#define SEC_PARAM_MAX_KEY_SIZE          16                                          /**< Maximum encryption key size. */


void sec_params_init(ble_gap_sec_params_t *m_sec_params)
{
    m_sec_params->timeout      = SEC_PARAM_TIMEOUT;
    m_sec_params->bond         = SEC_PARAM_BOND;
    m_sec_params->mitm         = SEC_PARAM_MITM;
    m_sec_params->io_caps      = SEC_PARAM_IO_CAPABILITIES;
    m_sec_params->oob          = SEC_PARAM_OOB;
    m_sec_params->min_key_size = SEC_PARAM_MIN_KEY_SIZE;
    m_sec_params->max_key_size = SEC_PARAM_MAX_KEY_SIZE;
}