/*
 * OLPC HGPK (XO-1) touchpad PS/2 mouse driver
 */

#ifndef _HGPK_H
#define _HGPK_H

#define HGPK_GS		0xff       /* The GlideSensor */
#define HGPK_PT		0xcf       /* The PenTablet */

enum hgpk_model_t {
	HGPK_MODEL_PREA = 0x0a,	/* pre-B1s */
	HGPK_MODEL_A = 0x14,	/* found on B1s, PT disabled in hardware */
	HGPK_MODEL_B = 0x28,	/* B2s, has capacitance issues */
	HGPK_MODEL_C = 0x3c,
	HGPK_MODEL_D = 0x50,	/* C1, mass production */
};

enum hgpk_mode {
	HGPK_MODE_MOUSE,
	HGPK_MODE_GLIDESENSOR,
	HGPK_MODE_PENTABLET,
	HGPK_MODE_INVALID
};

struct hgpk_data {
	struct psmouse *psmouse;
	enum hgpk_mode mode;
	bool powered;
	int count, x_tally, y_tally;	/* hardware workaround stuff */
	unsigned long recalib_window;
	struct delayed_work recalib_wq;
	int abs_x, abs_y;
};

#define hgpk_dbg(psmouse, format, arg...)		\
	dev_dbg(&(psmouse)->ps2dev.serio->dev, format, ## arg)
#define hgpk_err(psmouse, format, arg...)		\
	dev_err(&(psmouse)->ps2dev.serio->dev, format, ## arg)
#define hgpk_info(psmouse, format, arg...)		\
	dev_info(&(psmouse)->ps2dev.serio->dev, format, ## arg)
#define hgpk_warn(psmouse, format, arg...)		\
	dev_warn(&(psmouse)->ps2dev.serio->dev, format, ## arg)
#define hgpk_notice(psmouse, format, arg...)		\
	dev_notice(&(psmouse)->ps2dev.serio->dev, format, ## arg)

#ifdef CONFIG_MOUSE_PS2_OLPC
void hgpk_module_init(void);
int hgpk_detect(struct psmouse *psmouse, bool set_properties);
int hgpk_init(struct psmouse *psmouse);
#else
static inline void hgpk_module_init(void)
{
}
static inline int hgpk_detect(struct psmouse *psmouse, bool set_properties)
{
	return -ENODEV;
}
static inline int hgpk_init(struct psmouse *psmouse)
{
	return -ENODEV;
}
#endif

#endif
