/*
 *  Copyright (C) 2014-2015 Samsung Electronics
 *  Przemyslaw Marczak <p.marczak@samsung.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _INCLUDE_REGULATOR_H_
#define _INCLUDE_REGULATOR_H_

/**
 * U-Boot Voltage/Current Regulator
 * ================================
 *
 * The regulator API is based on a driver model, with the device tree support.
 * And this header describes the functions and data types for the uclass id:
 * 'UCLASS_REGULATOR' and the regulator driver API.
 *
 * The regulator uclass - is based on uclass platform data which is allocated,
 * automatically for each regulator device on bind and 'dev->uclass_platdata'
 * points to it. The data type is: 'struct dm_regulator_uclass_platdata'.
 * The uclass file: 'drivers/power/regulator/regulator-uclass.c'
 *
 * The regulator device - is based on driver's model 'struct udevice'.
 * The API can use regulator name in two meanings:
 * - devname  - the regulator device's name: 'dev->name'
 * - platname - the device's platdata's name. So in the code it looks like:
 *              'uc_pdata = dev->uclass_platdata'; 'name = uc_pdata->name'.
 *
 * The regulator device driver - provide an implementation of uclass operations
 * pointed by 'dev->driver->ops' as a struct of type 'struct dm_regulator_ops'.
 *
 * To proper bind the regulator device, the device tree node should provide
 * regulator constraints, like in the example below:
 *
 * ldo1 {
 *      regulator-name = "VDD_MMC_1.8V";     (mandatory for bind)
 *      regulator-min-microvolt = <1000000>; (optional)
 *      regulator-max-microvolt = <1000000>; (optional)
 *      regulator-min-microamp = <1000>;     (optional)
 *      regulator-max-microamp = <1000>;     (optional)
 *      regulator-always-on;                 (optional)
 *      regulator-boot-on;                   (optional)
 * };
 *
 * Please take a notice, that for the proper operation at least name constraint
 * is needed, e.g. for call the device_by_platname(...).
 *
 * Regulator bind:
 * For each regulator device, the device_bind() should be called with passed
 * device tree offset. This is required for this uclass's '.post_bind' method,
 * which do the scan on the device node, for the 'regulator-name' constraint.
 * If the parent is not a PMIC device, and the child is not bind by function:
 * 'pmic_bind_childs()', then it's recommended to bind the device by call to
 * dm_scan_fdt_node() - this is usually done automatically for bus devices,
 * as a post bind method.
 * Having the device's name constraint, we can call regulator_by_platname(),
 * to find interesting regulator. Before return, the regulator is probed,
 * and the rest of its constraints are put into the device's uclass platform
 * data, by the uclass regulator '.pre_probe' method.
 *
 * For more info about PMIC bind, please refer to file: 'include/power/pmic.h'
 *
 * Note:
 * Please do not use the device_bind_by_name() function, since it pass '-1' as
 * device node offset - and the bind will fail on uclass .post_bind method,
 * because of missing 'regulator-name' constraint.
 *
 *
 * Fixed Voltage/Current Regulator
 * ===============================
 *
 * When fixed voltage regulator is needed, then enable the config:
 * - CONFIG_DM_REGULATOR_FIXED
 *
 * The driver file: 'drivers/power/regulator/fixed.c', provides basic support
 * for control the GPIO, and return the device tree constraint values.
 *
 * To bind the fixed voltage regulator device, we usually use a 'simple-bus'
 * node as a parent. And 'regulator-fixed' for the driver compatible. This is
 * the same as in the kernel. The example node of fixed regulator:
 *
 * simple-bus {
 *     compatible = "simple-bus";
 *     #address-cells = <1>;
 *     #size-cells = <0>;
 *
 *     blue_led {
 *         compatible = "regulator-fixed";
 *         regulator-name = "VDD_LED_3.3V";
 *         regulator-min-microvolt = <3300000>;
 *         regulator-max-microvolt = <3300000>;
 *         gpio = <&gpc1 0 GPIO_ACTIVE_LOW>;
 *     };
 * };
 *
 * The fixed regulator devices also provide regulator uclass platform data. And
 * devices bound from such node, can use the regulator drivers API.
*/

/* enum regulator_type - used for regulator_*() variant calls */
enum regulator_type {
	REGULATOR_TYPE_LDO = 0,
	REGULATOR_TYPE_BUCK,
	REGULATOR_TYPE_DVS,
	REGULATOR_TYPE_FIXED,
	REGULATOR_TYPE_OTHER,
};

/**
 * struct dm_regulator_mode - this structure holds an information about
 * each regulator operation mode. Probably in most cases - an array.
 * This will be probably a driver-static data, since it is device-specific.
 *
 * @id             - a driver-specific mode id
 * @register_value - a driver-specific value for its mode id
 * @name           - the name of mode - used for regulator command
 * Note:
 * The field 'id', should be always a positive number, since the negative values
 * are reserved for the errno numbers when returns the mode id.
 */
struct dm_regulator_mode {
	int id; /* Set only as >= 0 (negative value is reserved for errno) */
	int register_value;
	const char *name;
};

/**
 * struct dm_regulator_uclass_platdata - pointed by dev->uclass_platdata, and
 * allocated on each regulator bind. This structure holds an information
 * about each regulator's constraints and supported operation modes.
 * There is no "step" voltage value - so driver should take care of this.
 *
 * @type       - one of 'enum regulator_type'
 * @mode       - pointer to the regulator mode (array if more than one)
 * @mode_count - number of '.mode' entries
 * @min_uV*    - minimum voltage (micro Volts)
 * @max_uV*    - maximum voltage (micro Volts)
 * @min_uA*    - minimum amperage (micro Amps)
 * @max_uA*    - maximum amperage (micro Amps)
 * @always_on* - bool type, true or false
 * @boot_on*   - bool type, true or false
 * @name**     - fdt regulator name - should be taken from the device tree
 *
 * Note:
 * *  - set automatically on device probe by the uclass's '.pre_probe' method.
 * ** - set automatically on device bind by the uclass's '.post_bind' method.
 * The constraints: type, mode, mode_count, can be set by device driver, e.g.
 * by the driver '.probe' method.
 */
struct dm_regulator_uclass_platdata {
	enum regulator_type type;
	struct dm_regulator_mode *mode;
	int mode_count;
	int min_uV;
	int max_uV;
	int min_uA;
	int max_uA;
	bool always_on;
	bool boot_on;
	const char *name;
};

/* Regulator device operations */
struct dm_regulator_ops {
	/**
	 * The regulator output value function calls operates on a micro Volts.
	 *
	 * get/set_value - get/set output value of the given output number
	 * @dev          - regulator device
	 * Sets:
	 * @uV           - set the output value [micro Volts]
	 * @return output value [uV] on success or negative errno if fail.
	 */
	int (*get_value)(struct udevice *dev);
	int (*set_value)(struct udevice *dev, int uV);

	/**
	 * The regulator output current function calls operates on a micro Amps.
	 *
	 * get/set_current - get/set output current of the given output number
	 * @dev            - regulator device
	 * Sets:
	 * @uA           - set the output current [micro Amps]
	 * @return output value [uA] on success or negative errno if fail.
	 */
	int (*get_current)(struct udevice *dev);
	int (*set_current)(struct udevice *dev, int uA);

	/**
	 * The most basic feature of the regulator output is its enable state.
	 *
	 * get/set_enable - get/set enable state of the given output number
	 * @dev           - regulator device
	 * Sets:
	 * @enable         - set true - enable or false - disable
	 * @return true/false for get; or 0 / -errno for set.
	 */
	bool (*get_enable)(struct udevice *dev);
	int (*set_enable)(struct udevice *dev, bool enable);

	/**
	 * The 'get/set_mode()' function calls should operate on a driver-
	 * specific mode definitions, which should be found in:
	 * field 'mode' of struct mode_desc.
	 *
	 * get/set_mode - get/set operation mode of the given output number
	 * @dev         - regulator device
	 * Sets
	 * @mode_id     - set output mode id (struct dm_regulator_mode->id)
	 * @return id/0 for get/set on success or negative errno if fail.
	 * Note:
	 * The field 'id' of struct type 'dm_regulator_mode', should be always
	 * positive number, since the negative is reserved for the error.
	 */
	int (*get_mode)(struct udevice *dev);
	int (*set_mode)(struct udevice *dev, int mode_id);
};

/**
 * regulator_mode: returns a pointer to the array of regulator mode info
 *
 * @dev        - pointer to the regulator device
 * @modep      - pointer to the returned mode info array
 * @return     - count of modep entries on success or negative errno if fail.
 */
int regulator_mode(struct udevice *dev, struct dm_regulator_mode **modep);

/**
 * regulator_get_value: get microvoltage voltage value of a given regulator
 *
 * @dev    - pointer to the regulator device
 * @return - positive output value [uV] on success or negative errno if fail.
 */
int regulator_get_value(struct udevice *dev);

/**
 * regulator_set_value: set the microvoltage value of a given regulator.
 *
 * @dev    - pointer to the regulator device
 * @uV     - the output value to set [micro Volts]
 * @return - 0 on success or -errno val if fails
 */
int regulator_set_value(struct udevice *dev, int uV);

/**
 * regulator_get_current: get microampere value of a given regulator
 *
 * @dev    - pointer to the regulator device
 * @return - positive output current [uA] on success or negative errno if fail.
 */
int regulator_get_current(struct udevice *dev);

/**
 * regulator_set_current: set the microampere value of a given regulator.
 *
 * @dev    - pointer to the regulator device
 * @uA     - set the output current [micro Amps]
 * @return - 0 on success or -errno val if fails
 */
int regulator_set_current(struct udevice *dev, int uA);

/**
 * regulator_get_enable: get regulator device enable state.
 *
 * @dev    - pointer to the regulator device
 * @return - true/false of enable state
 */
bool regulator_get_enable(struct udevice *dev);

/**
 * regulator_set_enable: set regulator enable state
 *
 * @dev    - pointer to the regulator device
 * @enable - set true or false
 * @return - 0 on success or -errno val if fails
 */
int regulator_set_enable(struct udevice *dev, bool enable);

/**
 * regulator_get_mode: get mode of a given device regulator
 *
 * @dev    - pointer to the regulator device
 * @return - positive  mode number on success or -errno val if fails
 * Note:
 * The regulator driver should return one of defined, mode number rather, than
 * the raw register value. The struct type 'mode_desc' provides a field 'mode'
 * for this purpose and register_value for a raw register value.
 */
int regulator_get_mode(struct udevice *dev);

/**
 * regulator_set_mode: set given regulator mode
 *
 * @dev    - pointer to the regulator device
 * @mode   - mode type (field 'mode' of struct mode_desc)
 * @return - 0 on success or -errno value if fails
 * Note:
 * The regulator driver should take one of defined, mode number rather
 * than a raw register value. The struct type 'regulator_mode_desc' has
 * a mode field for this purpose and register_value for a raw register value.
 */
int regulator_set_mode(struct udevice *dev, int mode);

/**
 * regulator_by_platname_autoset_and_enable: setup the regulator given by
 * its uclass's platform data '.name'. The setup depends on constraints found
 * in device's uclass's platform data (struct dm_regulator_uclass_platdata):
 * - Voltage value - will set - if '.min_uV' and '.max_uV' values are equal
 * - Current limit - will set - if '.min_uA' and '.max_uA' values are equal
 * - Enable - will set - if any of: '.always_on' or '.boot_on', is set to true
 *
 * The function returns on first encountered error.
 *
 * @platname - expected string for dm_regulator_uclass_platdata .name field
 * @devp      - returned pointer to the regulator device - if non-NULL passed
 * @verbose   - (true/false) print regulator setup info, or be quiet
 * @return: 0 on success or negative value of errno.
 *
 * The returned 'regulator' device can be used with:
 * - regulator_get/set_*
 * For shorter call name, the below macro regulator_autoset() can be used.
 */
int regulator_by_platname_autoset_and_enable(const char *platname,
					     struct udevice **devp,
					     bool verbose);

#define regulator_autoset(platname, devp, verbose) \
	regulator_by_platname_autoset_and_enable(platname, devp, verbose)

/**
 * regulator_by_platname_list_autoset_and_enable: setup the regulators given by
 * list of its uclass's platform data '.name'. The setup depends on constraints
 * found in device's uclass's platform data. The function loops with calls to:
 * regulator_by_platname_autoset_and_enable() for each name of list.
 *
 * @list_platname - an array of expected strings for .name field of each
 *                  regulator's uclass platdata
 * @list_entries  - number of regulator's name list entries
 * @list_devp     - an array of returned pointers to the successfully setup
 *                  regulator devices if non-NULL passed
 * @verbose       - (true/false) print each regulator setup info, or be quiet
 * @return 0 on successfully setup of all list entries or 1 otwerwise.
 *
 * The returned 'regulator' devices can be used with:
 * - regulator_get/set_*
 * For shorter call name, the below macro regulator_list_autoset() can be used.
 */
int regulator_by_platname_list_autoset_and_enable(const char *list_platname[],
						  int list_entries,
						  struct udevice *list_devp[],
						  bool verbose);

#define regulator_list_autoset(namelist, entries, devlist, verbose)      \
	regulator_by_platname_list_autoset_and_enable(namelist, entries, \
						      devlist, verbose)

/**
 * regulator_by_devname: returns the pointer to the pmic regulator device.
 *                       Search by name, found in regulator device's name.
 *
 * @devname - expected string for 'dev->name' of regulator device
 * @devp    - returned pointer to the regulator device
 * @return 0 on success or negative value of errno.
 *
 * The returned 'regulator' device can be used with:
 * - regulator_get/set_*
 */
int regulator_by_devname(const char *devname, struct udevice **devp);

/**
 * regulator_by_platname: returns the pointer to the pmic regulator device.
 *                        Search by name, found in regulator uclass platdata.
 *
 * @platname - expected string for uc_pdata->name of regulator uclass platdata
 * @devp     - returned pointer to the regulator device
 * @return 0 on success or negative value of errno.
 *
 * The returned 'regulator' device can be used with:
 * - regulator_get/set_*
 */
int regulator_by_platname(const char *platname, struct udevice **devp);

#endif /* _INCLUDE_REGULATOR_H_ */
