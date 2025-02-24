#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const double defaultopacity  = 0.75;
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#001177";
static char selbgcolor[]            = "#001177";
static char *colors[][3] = {
        /*               fg           bg           border   */
         [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
         [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9","10" };

/* Lockfile */
static char lockfile[] = "/tmp/dwm.lock";

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
  #define KEYEVENT(SRC_MOD,SRC_KEY,DST_MOD,DST_KEY) \
	{ SRC_MOD, SRC_KEY, sendkeyevent, { .v = &(const KeyBinding){ DST_MOD, DST_KEY } } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *upbrightness[]   = { "xbacklight", "-inc", "10", NULL };
static const char *downbrightness[] = { "xbacklight", "-dec", "10", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
  { MODKEY|ShiftMask,		          XK_s,	     spawn,	         SHCMD("transset-df -a --dec .1") },
 	{ MODKEY|ShiftMask,		          XK_d,	     spawn,	         SHCMD("transset-df -a --inc .1") },
 	{ MODKEY|ShiftMask,		          XK_f,	     spawn,	         SHCMD("transset-df -a .75") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  { MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
 	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	// Navigation(two-handed)
	KEYEVENT(Mod1Mask, XK_h, 0, XK_Left)
	KEYEVENT(Mod1Mask, XK_l, 0, XK_Right)
	KEYEVENT(Mod1Mask, XK_k, 0, XK_Up)
	KEYEVENT(Mod1Mask, XK_j, 0, XK_Down)
	KEYEVENT(Mod1Mask, XK_p, 0, XK_Up)
	KEYEVENT(Mod1Mask, XK_n, 0, XK_Down)
	KEYEVENT(Mod1Mask, XK_i, ControlMask, XK_Left)
	KEYEVENT(Mod1Mask, XK_o, ControlMask, XK_Right)
	KEYEVENT(Mod1Mask, XK_equal, ControlMask, XK_Home)
	KEYEVENT(Mod1Mask, XK_minus, ControlMask, XK_End)
	// Navigation(one-handed)
	KEYEVENT(Mod1Mask, XK_s, 0, XK_Up)
	KEYEVENT(Mod1Mask, XK_x, 0, XK_Down)
	KEYEVENT(Mod1Mask, XK_z, 0, XK_Left)
	KEYEVENT(Mod1Mask, XK_c, 0, XK_Right)
	KEYEVENT(Mod1Mask, XK_d, 0, XK_Return)
	KEYEVENT(Mod1Mask, XK_a, 0, XK_Home)
	KEYEVENT(Mod1Mask, XK_e, 0, XK_End)
	// Selection(two-handed)
	KEYEVENT(Mod1Mask|ShiftMask, XK_h, ShiftMask, XK_Left)
	KEYEVENT(Mod1Mask|ShiftMask, XK_l, ShiftMask, XK_Right)
	KEYEVENT(Mod1Mask|ShiftMask, XK_k, ShiftMask, XK_Up)
	KEYEVENT(Mod1Mask|ShiftMask, XK_j, ShiftMask, XK_Down)
	KEYEVENT(Mod1Mask|ShiftMask, XK_p, ShiftMask, XK_Up)
	KEYEVENT(Mod1Mask|ShiftMask, XK_n, ShiftMask, XK_Down)
	KEYEVENT(Mod1Mask|ShiftMask, XK_i, ControlMask|ShiftMask, XK_Left)
	KEYEVENT(Mod1Mask|ShiftMask, XK_o, ControlMask|ShiftMask, XK_Right)
	KEYEVENT(Mod1Mask|ShiftMask, XK_equal, ControlMask|ShiftMask, XK_Home)
	KEYEVENT(Mod1Mask|ShiftMask, XK_minus, ControlMask|ShiftMask, XK_End)
	// Selection(one-handed)
	KEYEVENT(Mod1Mask|ShiftMask, XK_s, ShiftMask, XK_Up)
	KEYEVENT(Mod1Mask|ShiftMask, XK_x, ShiftMask, XK_Down)
	KEYEVENT(Mod1Mask|ShiftMask, XK_z, ShiftMask, XK_Left)
	KEYEVENT(Mod1Mask|ShiftMask, XK_c, ShiftMask, XK_Right)
	KEYEVENT(Mod1Mask|ShiftMask, XK_a, ShiftMask, XK_Home)
	KEYEVENT(Mod1Mask|ShiftMask, XK_e, ShiftMask, XK_End)
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
 	{ 0,            XF86XK_MonBrightnessUp,    spawn,          {.v = upbrightness } },
	{ 0,            XF86XK_MonBrightnessDown,  spawn,          {.v = downbrightness } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

