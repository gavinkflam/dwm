/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[] = {
	"mono:size=10:antialias=true:autohint=true"
};
static const char dmenufont[]       = "Hack:size=10";
static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#222222";
static const char col_gray3[]       = "#aaaaaa";
static const char col_gray4[]       = "#dddddd";
static const char col_cyan[]        = "#000000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask /* super key as modkey */
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *lockcmd[]  = { "xset", "s", "activate", NULL };

static const char *fmcmd[]      = { "pcmanfm", NULL };
static const char *browsercmd[] = { "chromium", NULL };
static const char *printcmd[]   = { "flameshot", "gui", NULL };
static const char *passcmd[]    = { "passmenu", NULL };

static const char *brightnessdowncmd[] = { "brightnessctl", "s", "5%-", NULL };
static const char *brightnessupcmd[]   = { "brightnessctl", "s", "5%+", NULL };
static const char *volumetogglecmd[]   = { "amixer", "set", "Master", "toggle", NULL };
static const char *volumedowncmd[]     = { "amixer", "set", "Master", "5%-", NULL };
static const char *volumeupcmd[]       = { "amixer", "set", "Master", "5%+", NULL };

static Key keys[] = {
	/* modifier              key                      function        argument */
	{ MODKEY,                XK_d,                    spawn,          {.v = dmenucmd } },
	{ MODKEY,                XK_n,                    spawn,          {.v = termcmd } },
	{ MODKEY,                XK_Escape,               spawn,          {.v = lockcmd } },
	{ MODKEY,                XK_e,                    spawn,          {.v = fmcmd } },
	{ MODKEY,                XK_i,                    spawn,          {.v = browsercmd } },
	{ MODKEY,                XK_p,                    spawn,          {.v = printcmd } },
	{ MODKEY,                XK_s,                    spawn,          {.v = passcmd } },
	{ MODKEY,                XK_F1,                   spawn,          {.v = brightnessdowncmd } },
	{ MODKEY,                XK_F2,                   spawn,          {.v = brightnessupcmd } },
	{ MODKEY,                XK_F10,                  spawn,          {.v = volumetogglecmd } },
	{ MODKEY,                XK_F11,                  spawn,          {.v = volumedowncmd } },
	{ MODKEY,                XK_F12,                  spawn,          {.v = volumeupcmd } },
	{ MODKEY,                XK_b,                    togglebar,      {0} },
	{ MODKEY,                XK_j,                    focusstack,     {.i = +1 } },
	{ MODKEY,                XK_k,                    focusstack,     {.i = -1 } },
	{ MODKEY,                XK_h,                    incnmaster,     {.i = +1 } },
	{ MODKEY,                XK_l,                    incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,      XK_h,                    setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,      XK_l,                    setmfact,       {.f = +0.05} },
	{ MODKEY,                XK_z,                    zoom,           {0} },
	{ MODKEY,                XK_Tab,                  view,           {0} },
	{ MODKEY|ShiftMask,      XK_q,                    killclient,     {0} },
	{ MODKEY,                XK_t,                    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                XK_f,                    setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                XK_m,                    setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                XK_space,                setlayout,      {0} },
	{ MODKEY|ShiftMask,      XK_space,                togglefloating, {0} },
	{ MODKEY,                XK_0,                    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,      XK_0,                    tag,            {.ui = ~0 } },
	{ MODKEY,                XK_comma,                focusmon,       {.i = -1 } },
	{ MODKEY,                XK_period,               focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,      XK_comma,                tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,      XK_period,               tagmon,         {.i = +1 } },
	TAGKEYS(                 XK_grave,                                0)
	TAGKEYS(                 XK_1,                                    1)
	TAGKEYS(                 XK_2,                                    2)
	TAGKEYS(                 XK_3,                                    3)
	TAGKEYS(                 XK_4,                                    4)
	TAGKEYS(                 XK_5,                                    5)
	TAGKEYS(                 XK_6,                                    6)
	TAGKEYS(                 XK_7,                                    7)
	TAGKEYS(                 XK_8,                                    8)
	TAGKEYS(                 XK_9,                                    9)
	{ MODKEY|ShiftMask,      XK_x,                    quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

