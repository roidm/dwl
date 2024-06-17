#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus                = 1;  /* focus follows mouse */
static const int bypass_surface_visibility  = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const int smartgaps                  = 0;  /* 1 means no outer gap when there is only one window */
static const int monoclegaps                = 0;  /* 1 means outer gaps in monocle layout */
static const unsigned int borderpx          = 1;  /* border pixel of windows */
static const unsigned int gappih            = 20; /* horiz inner gap between windows */
static const unsigned int gappiv            = 20; /* vert inner gap between windows */
static const unsigned int gappoh            = 14; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov            = 20; /* vert outer gap between windows and screen edge */
static const float rootcolor[]              = COLOR(0x2a2a2aff);
static const float bordercolor[]            = COLOR(0x2c2c2cff);
static const float focuscolor[]             = COLOR(0x2a2a2aff);
static const float urgentcolor[]            = COLOR(0x8CCE2Fff);

/* To conform the xdg-protocol, set the Slpha to zero to restore the old behavior */
static const float fullscreen_bg[]          = {0.1f, 0.1f, 0.1f, 0.0f}; /* You can also use glsl colors */
static const int center_relative_to_monitor = 0;          /* 0 means center floating relative to the window area  */
static const char cursortheme[]		          = "Adwaita";  /* theme from /usr/share/cursors/xorg-x11 */
static const unsigned int cursorsize	      = 24;

static const int opacity = 0;               /* flag to enable opacity */
static const float opacity_inactive = 1.0;
static const float opacity_active = 1.0;

static const int shadow = 1;                /* flag to enable shadow */
static const int shadow_only_floating = 0;  /* only apply shadow to floating windows */
static const struct wlr_render_color shadow_color = COLOR(0x00000Fff);
static const struct wlr_render_color shadow_color_focus = COLOR(0x00000Fff);
static const int corner_radius = 0; /* 0 disables corner_radius */
static const char *const shadow_ignore_list[] = { 
		
	//"xdg-desktop-portal-gtk", NULL 
	NULL
	
}; /* list of app-id to ignore */

/*Blur*/
static const int shadow_blur_sigma = 10;
static const int shadow_blur_sigma_focus = 20;
static const int blur = 0; /* flag to enable blur */
static const int blur_optimized = 1;
static const int blur_ignore_transparent = 1;
static const struct blur_data blur_data = {
	.radius = 5,
	.num_passes = 3,
	.noise = (float)0.02,
	.brightness = (float)0.9,
	.contrast = (float)0.9,
	.saturation = (float)1.1,
};


/* tagging - TAGCOUNT must be no greater than 31 */
#define TAGCOUNT (9)

/* logging */
static int log_level = WLR_ERROR;

static const Env envs[] = {
    /* variable            value */
	NULL,
};

/* Autostart */
static const char *const autostart[] = {
	"systemctl",
    "--user",
    "start",
    "xdg-desktop-portal",
    "xdg-desktop-portal-wlr",
    NULL,
    "dbus-update-activation-environment",
    "--systemd",
    "WAYLAND_DISPLAY",
    "XDG_CURRENT_DESKTOP",
    NULL,
	  "start", NULL,
	NULL /* terminate */
};

static const Rule rules[] = {
	/* app_id                    title          tags mask          isfloating   monitor    scratchkey */
	//{ "firefox",                 NULL,             1 << 8,             0,           -1,        0 },
	{ NULL,                      "scratchpad",     0,                  1,           -1,       's'},

};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
/* NOTE: ALWAYS add a fallback rule, even if you are completely sure it won't be used */
static const MonitorRule monrules[] = {
	/* name       mfact  nmaster scale layout       rotate/reflect                   x  y resx resy rate mode adaptive */
	/* example of a HiDPI laptop monitor as 120hz: */
	{ "DP-2",    0.50f,  1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   0, 0, 2560, 1440, 119.871f, 2, 0}, /* Razer Display */
	{ "DP-3",    0.50f,  1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1, -1, 1920, 1080, 99.999f, 0, 0}, /* Lenovo ThinkVision */
	/* defaults */
	{ NULL,	      0.50f,  1,      1,   &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   0, 0, 0, 0, 0.0f, 0, 0},
	/* mode lets the user decide whether dwl should set mode or whether mode should be custom (-1). see wlr-randr */
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
    .layout = "es",
	.options = NULL,
};

static const int repeat_rate = 25;
static const int repeat_delay = 300;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 1;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;

/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;
/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define M WLR_MODIFIER_LOGO
#define A WLR_MODIFIER_ALT
#define S WLR_MODIFIER_SHIFT
#define C WLR_MODIFIER_CTRL

#define TAGKEYS(KEY,TAG) \
	{ M,     KEY,            view,            {.ui = 1 << TAG} }, \
	{ M|C,   KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ M|S,   KEY,            tag,             {.ui = 1 << TAG} }, \
	{ M|C|S, KEY,            toggletag,       {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]      = { "wezterm", NULL };
static const char *menucmd[]      = { "wfi", NULL };
static const char *up_vol[]       = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%",  NULL};
static const char *down_vol[]     = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL};
static const char *mute_vol[]     = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL};
static const char *forward[]      = { "playerctl", "next", NULL};
static const char *backward[]     = { "playerctl", "previous", NULL};
static const char *play[]         = { "playerctl", "play-pause", NULL};

/* named scratchpads - First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = { "s", "foot", "-T", "scratchpad", NULL };

#include "keys.h"
static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */
	{ M,                    Key_d,          spawn,          {.v = menucmd} },
	{ M,                    Key_Return,     spawn,          {.v = termcmd} },
	{ A,                    Key_t,          togglescratch,  {.v = scratchpadcmd } },
	{ M,                    Key_p,          focusortogglescratch, {.v = scratchpadcmd } },
	{ M|S,                  Key_p,          focusortogglematchingscratch, {.v = scratchpadcmd } },
	{ M,                    Key_b,          togglebar,      {0} },
	{ M,                    Key_j,          focusstack,     {.i = +1} },
	{ M,                    Key_k,          focusstack,     {.i = -1} },
	{ M,                    Key_h,          setmfact,       {.f = -0.01f} },
	{ M,                    Key_l,          setmfact,       {.f = +0.01f} },
	{ M|S,                  Key_j,          movestack,      {.i = +1} },
	{ M|S,                  Key_k,          movestack,      {.i = -1} },
	{ M|A,                  Key_h,          incgaps,        {.i = +1 } },
	{ M|A,                  Key_l,          incgaps,        {.i = -1 } },
	{ M|A|S,                Key_h,          incogaps,       {.i = +1 } },
	{ M|A|S,                Key_l,          incogaps,       {.i = -1 } },
	{ M|A|C,                Key_h,          incigaps,       {.i = +1 } },
	{ M|A|C,                Key_l,          incigaps,       {.i = -1 } },
	{ M|A,                  Key_0,          togglegaps,     {0} },
	{ M|A|S,                Key_parenright, defaultgaps,    {0} },
	{ M,                    Key_z,          zoom,           {0} },
	{ M,                    Key_Tab,        view,           {0} },
	{ M,                    Key_q,          killclient,     {0} },
	{ M,                    Key_t,          setlayout,      {.v = &layouts[0]} },
	{ M|S,                  Key_f,          setlayout,      {.v = &layouts[1]} },
	{ M|S,                  Key_m,          setlayout,      {.v = &layouts[2]} },
	{ M,                    Key_space,      setlayout,      {0} },
	{ M|S,                  Key_space,      togglefloating, {0} },
	{ M,                    Key_e,          togglefullscreen, {0} },
	{ M,                    Key_c,          movecenter,     {0} },
	{ M,                    Key_0,          view,           {.ui = ~0} },
	{ M|S,                  Key_parenright, tag,            {.ui = ~0} },
	{ M,                    Key_comma,      focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ M,                    Key_period,     focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ M|S,                  Key_comma,      tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ M|S,                  Key_period,     tagmon,         {.i = WLR_DIRECTION_RIGHT} },
	{ M|S,                  Key_q,          quit,           {0} },

  /*TAGKEYS*/
    TAGKEYS(                Key_1,			0),
	TAGKEYS(                Key_2,			1),
	TAGKEYS(                Key_3,			2),
	TAGKEYS(                Key_4,			3),
	TAGKEYS(                Key_5,			4),
	TAGKEYS(                Key_6,			5),
	TAGKEYS(                Key_7,			6),
	TAGKEYS(                Key_8,			7),
	TAGKEYS(                Key_9,			8),


	/*Apps*/
	{ M,                    Key_x,          spawn,          SHCMD("nwg-bar -p center -a middle -i 48 -t bar.json -s preset-0.css")},
	{ M,                    Key_m,          spawn,          SHCMD("gnome-system-monitor")},
	{ M,                    Key_f,          spawn,          SHCMD("thunar")},
	{ M,                    Key_g,          spawn,          SHCMD("gthumb")},
	{ A,                    Key_d,          spawn,          SHCMD("gnome-disks")},
	{ A,                    Key_n,          spawn,          SHCMD("swaync-client -t")},
	{ A,                    Key_p,          spawn,          SHCMD("colorpicker")},
	{ 0,                    Key_Print,      spawn,          SHCMD("exec scshot --now")},
	{ S,                    Key_Print,      spawn,          SHCMD("exec scshot --area")},
	{ M,                    Key_n,          spawn,          SHCMD("foot -c $HOME/.config/foot/footnvim.ini -T scratchpad -e nvim")},
	{ A,                    Key_h,          spawn,          SHCMD("foot -T scratchpad -e btop")},
	{ A|S,                  Key_h,          spawn,          SHCMD("foot -T scratchpad -e htop")},

	/*Multimedia keys*/
	{ 0,          Key_XF86AudioMute,         spawn,        {.v = mute_vol } },
	{ 0,          Key_XF86AudioLowerVolume,  spawn,        {.v = down_vol } },
	{ 0,          Key_XF86AudioRaiseVolume,  spawn,        {.v = up_vol } },
	{ 0,          Key_XF86AudioNext,         spawn,        {.v = forward } },
	{ 0,          Key_XF86AudioPrev,         spawn,        {.v = backward } },
	{ 0,          Key_XF86AudioPlay,         spawn,        {.v = play } },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ C|A,Key_BackSpace, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(KEY,n) { C|A, KEY, chvt, {.ui = (n)} } 
	CHVT(Key_F1, 1), CHVT(Key_F2,  2),  CHVT(Key_F3,  3),  CHVT(Key_F4,  4),
	CHVT(Key_F5, 5), CHVT(Key_F6,  6),  CHVT(Key_F7,  7),  CHVT(Key_F8,  8),
	CHVT(Key_F9, 9), CHVT(Key_F10, 10), CHVT(Key_F11, 11), CHVT(Key_F12, 12),
};


static const Button buttons[] = {
	{ M, BTN_LEFT,      moveresize, {.ui = CurMove} },
	{ M, BTN_MIDDLE,    moveresize, {.ui = Curmfact} },
	{ M, BTN_RIGHT,     moveresize, {.ui = CurResize} },
};
