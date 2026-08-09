static void tile(Monitor *m);
static void center_tile(Monitor *m);
static void right_tile(Monitor *m);
static void overview(Monitor *m);
static void grid(Monitor *m);
static void scroller(Monitor *m);
static void deck(Monitor *mon);
static void monocle(Monitor *m);
static void vertical_tile(Monitor *m);
static void vertical_overview(Monitor *m);
static void vertical_grid(Monitor *m);
static void vertical_scroller(Monitor *m);
static void vertical_deck(Monitor *mon);
static void dwindle(Monitor *m);
static void fair(Monitor *m);
static void vertical_fair(Monitor *m);
static void vertical_reallyfair(Monitor *m);

/* vertical_reallyfair grid shape: 2 rows for two windows, else 3 rows.
 * Shared by the arrange, resize and set_proportion paths so the row-count
 * logic only ever lives in one place. row_cols[i] is the column count of row
 * i (row 0 is the master row and always holds exactly one window). */
static inline void reallyfair_compute_rows(int32_t n, int32_t *out_rows,
										   int32_t out_row_cols[3]) {
	int32_t rows = (n >= 3) ? 3 : 2;
	int32_t row1_cnt = (n - 1) / 2;
	int32_t row2_cnt = n - 1 - row1_cnt;
	out_row_cols[0] = 1;
	out_row_cols[1] = (rows > 1) ? ((n >= 3) ? row1_cnt : n - 1) : 0;
	out_row_cols[2] = (rows > 2) ? row2_cnt : 0;
	*out_rows = rows;
}

/* layout(s) */
Layout overviewlayout = {"󰃇", overview, "overview"};

enum {
	TILE,
	SCROLLER,
	GRID,
	MONOCLE,
	DECK,
	CENTER_TILE,
	VERTICAL_SCROLLER,
	VERTICAL_TILE,
	VERTICAL_GRID,
	VERTICAL_DECK,
	RIGHT_TILE,
	DWINDLE,
	FAIR,
	VERTICAL_FAIR,
	VERTICAL_REALLYFAIR,
};

Layout layouts[] = {
	// 最少两个,不能删除少于两个
	/* symbol     arrange function   name */
	{"T", tile, "tile", TILE},						 // 平铺布局
	{"S", scroller, "scroller", SCROLLER},			 // 滚动布局
	{"G", grid, "grid", GRID},						 // 格子布局
	{"M", monocle, "monocle", MONOCLE},				 // 单屏布局
	{"K", deck, "deck", DECK},						 // 卡片布局
	{"CT", center_tile, "center_tile", CENTER_TILE}, // 居中布局
	{"RT", right_tile, "right_tile", RIGHT_TILE},	 // 右布局
	{"VS", vertical_scroller, "vertical_scroller",
	 VERTICAL_SCROLLER},								   // 垂直滚动布局
	{"VT", vertical_tile, "vertical_tile", VERTICAL_TILE}, // 垂直平铺布局
	{"VG", vertical_grid, "vertical_grid", VERTICAL_GRID}, // 垂直格子布局
	{"VK", vertical_deck, "vertical_deck", VERTICAL_DECK}, // 垂直卡片布局
	{"DW", dwindle, "dwindle", DWINDLE},
	{"F", fair, "fair", FAIR},
	{"VF", vertical_fair, "vertical_fair", VERTICAL_FAIR},
	{"VRF", vertical_reallyfair, "vertical_reallyfair", VERTICAL_REALLYFAIR},
};
