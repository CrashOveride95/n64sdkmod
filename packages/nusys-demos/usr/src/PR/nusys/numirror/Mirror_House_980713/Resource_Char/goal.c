
/* niff to gfx converter v1.2 */

/* ============================================================
          Header Area
 ============================================================ */

#ifndef __ND_COMMONS__
#define __ND_COMMONS__

/* ------------------ macros */

#define SEGTOP(sno) ((u32)(sno)<<24)
#define SEGADRS(sno,adrs) (SEGTOP(sno)|((u32)(adrs)&0x00ffffff))

/* ------------------ geometric animation */

enum{
  /* NDR_ANIM_CHANNEL.kind */
  NDC_ANIMKIND_TRS_X  = 0x00,
  NDC_ANIMKIND_TRS_Y  = 0x01,
  NDC_ANIMKIND_TRS_Z  = 0x02,
  NDC_ANIMKIND_ROT_X  = 0x03,
  NDC_ANIMKIND_ROT_Y  = 0x04,
  NDC_ANIMKIND_ROT_Z  = 0x05,
  NDC_ANIMKIND_SCL_X  = 0x06,
  NDC_ANIMKIND_SCL_Y  = 0x07,
  NDC_ANIMKIND_SCL_Z  = 0x08
};

typedef struct {
  u16 kind;
  s16 start;
  s16 end;
  s16 nkey;
  s16 *key;
  float *value;
} NDR_ANIM_CHANNEL;

typedef struct {
  NDR_ANIM_CHANNEL *chlist;
  u16 nch;
  u16 total;
} NDR_ANIM;

/* ------------------ shape */

typedef struct{
  s16 *key;
  s16 *tblno;
  u16 nkey;
  u16 nelem;
} NDR_DEFORM;

typedef struct{
  Gfx *gfx;
  Vtx *vtx;
  u16 nvtx;
  u16 vtxsegno;

  /* using texture segment */
  u8 *img;
  u16 *tlut;
  u16 imgsegno, tlutsegno;

  /* shape deform data link */
  s16 *shaperef;
  NDR_DEFORM *vtx_deform;
  NDR_DEFORM *vtxcol_deform;
  NDR_DEFORM *vtxnv_deform;

} NDR_SHAPE;

/* ------------------ object */

enum{
  /* object types */
  NDC_TYPE_NULL = 0x01,
  NDC_TYPE_3D = 0x02,
  NDC_TYPE_BILLBOARD = 0x03,

  /* ColorCombine Mode */
  NDC_CC_COMBINED = 0x00,
  NDC_CC_TEX0 = 0x01,
  NDC_CC_TEX1 = 0x02,
  NDC_CC_PRIMITIVE = 0x03,
  NDC_CC_SHADE = 0x04,
  NDC_CC_ENV = 0x05,
  NDC_CC_KEY_CENTER = 0x10,
  NDC_CC_KEY_SCALE = 0x11,
  NDC_CC_COMBINED_ALPHA = 0x06,
  NDC_CC_TEX0_ALPHA = 0x07,
  NDC_CC_TEX1_ALPHA = 0x08,
  NDC_CC_PRIMITIVE_ALPHA = 0x09,
  NDC_CC_SHADE_ALPHA = 0x0a,
  NDC_CC_ENV_ALPHA = 0x0b,
  NDC_CC_LOD = 0x0c,
  NDC_CC_PRIM_LOD = 0x0d,
  NDC_CC_NOISE = 0x12,
  NDC_CC_K4 = 0x14,
  NDC_CC_K5 = 0x15,
  NDC_CC_1 = 0x0e,
  NDC_CC_0 = 0x0f,

  /* Render Mode(complexed) */
  NDC_RM_AA_EN                     = 0x80000000,
  NDC_RM_Z_CMP                     = 0x40000000,
  NDC_RM_Z_UPD                     = 0x20000000,
  NDC_RM_IM_RD                     = 0x10000000,
  NDC_RM_CVG_DST                   = 0x0c000000,
    NDC_RM_CVG_DST_CLAMP           = 0x00000000,
    NDC_RM_CVG_DST_WRAP            = 0x04000000,
    NDC_RM_CVG_DST_FULL            = 0x08000000,
    NDC_RM_CVG_DST_SAVE            = 0x0c000000,
  NDC_RM_CLR_ON_CVG                = 0x02000000,
  NDC_RM_CVG_X_ALPHA               = 0x01000000,
  NDC_RM_ALPHA_CVG_SEL             = 0x00800000,
  NDC_RM_FORCE_BL                  = 0x00400000,
  NDC_RM_ZMODE                     = 0x00300000,
    NDC_RM_ZMODE_OPA               = 0x00000000,
    NDC_RM_ZMODE_INTER             = 0x00100000,
    NDC_RM_ZMODE_XLU               = 0x00200000,
    NDC_RM_ZMODE_DEC               = 0x00300000,
  NDC_RM_ALPHA_COMPARE             = 0x000c0000,
    NDC_RM_ALPHA_COMPARE_NONE      = 0x00000000,
    NDC_RM_ALPHA_COMPARE_THRESHOLD = 0x00040000,
    NDC_RM_ALPHA_COMPARE_DITHER    = 0x00080000,
  NDC_RM_DITHER_ALPHA              = 0x00030000,
    NDC_RM_DITHER_ALPHA_PATTERN    = 0x00000000,
    NDC_RM_DITHER_ALPHA_NOPATTERN  = 0x00010000,
    NDC_RM_DITHER_ALPHA_NOISE      = 0x00020000,
    NDC_RM_DITHER_ALPHA_DISABLE    = 0x00030000,
  NDC_RM_BLENDER_MUX0              = 0x0000ff00,
  NDC_RM_BLENDER_MUX1              = 0x000000ff,

  /* NDR_OBJ.regflag(bit assign) */
  NDC_REGF_2CYC        = 0x4000
};

typedef struct{
  float tx, ty, tz;
  float rx, ry, rz;
  float sx, sy, sz;
} TRX;

typedef struct ndr_objTag{

  /* object propaties */
  u16 type, gid;
  u32 prio;
  TRX trx;

  /* resourse index */
  s16 shape;

  /* RSP, RDP status register setting */
  u16 regflag;
  u32 geommode;
  u32 rdmode;
  u32 primcol;
  u8 cc1[8], cc2[8];

  /* geometric animation setting */
  s16 geom_anim;
  u16 loop;
  u16 framerate;
  u32 order;

  /* children links */
  s16 bb_obj[2];
  u16 nchild;
  u16 *child;

} NDR_OBJ;

/* ------------------ scene */

typedef struct{
  TRX trx;
  u16 objno;
} NDR_SCN_INST_OBJ;

typedef struct{
  int type;
  u32 color;
  float x, y, z;
  float a1,a2;
} NDR_SCN_LIGHT;

typedef struct{
  struct{
    u16 near, far;
    u8 r,g,b,a;
  }fog;
  struct{
    u32 mode;
    float fovy, aspect, scale;
    u16 top, bottom, left, right, near, far;
    u16 eye_inst, upper_inst, lookat_inst;
  }cam;
  struct{
    u32 amb_color;
    int nlight;
    NDR_SCN_LIGHT *light;
  }light;
  u16 fill_col, fill_depth;
  NDR_SCN_INST_OBJ *entryobj;
  u16 nentobj;
} NDR_SCENE;

typedef struct{
  NDR_SCENE *scene;
  float convert_scale;

  NDR_OBJ **obj;
  NDR_SHAPE **shape;
  NDR_ANIM **anim;
  s16 **rawvtx;
  u32 **rawvtxcol;
  s8 **rawvtxnv;

  u16 nobj;
  u16 nanim;
  u16 nshape;
  u16 nrawvtx;
  u16 nrawvtxcol;
  u16 nrawvtxnv;
} NDR_RESINFO;

#endif    /* #ifndef __ND_COMMONS__ */

#ifdef PREVIEW_TYPE
#undef PREVIEW_TYPE
#endif  /* #ifdef PREVIEW_TYPE */

#ifdef RESINFO_NAME
#undef RESINFO_NAME
#endif  /* #ifdef RESINFO_NAME */

#define PREVIEW_TYPE 28
extern NDR_RESINFO resinfo_goal;
#define RESINFO_NAME resinfo_goal

static Gfx _goal_aligner0[] = { gsSPEndDisplayList() };

/* ============================================================
          Bitmap
 ============================================================ */
static u8 bmp_goal[] = {
/* name:GOAL  type:RGBA  pixel/bit: 32 bits
  offset:0x00000000  length:4096 bytes. */
0xf7,0x39,0x08,0x5a,0xf7,0x39,0x08,0x74,
0xf7,0x39,0x08,0x86,0xf7,0x39,0x08,0x90,
0xf7,0x39,0x08,0x95,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x95,
0xf7,0x39,0x08,0x90,0xf7,0x39,0x08,0x86,
0xf7,0x39,0x08,0x74,0xf7,0x39,0x08,0x5a,
0xf7,0x39,0x08,0x74,0xf7,0x39,0x08,0x95,
0xf7,0x39,0x08,0xad,0xf7,0x39,0x08,0xba,
0xf7,0x39,0x08,0xc0,0xf7,0x39,0x08,0xc2,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc2,0xf7,0x39,0x08,0xc0,
0xf7,0x39,0x08,0xba,0xf7,0x39,0x08,0xad,
0xf7,0x39,0x08,0x95,0xf7,0x39,0x08,0x74,
0xf7,0x39,0x08,0x86,0xf7,0x39,0x08,0xad,
0xf7,0x39,0x08,0xc8,0xf7,0x39,0x08,0xd7,
0xf7,0x39,0x08,0xdf,0xf7,0x39,0x08,0xe1,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xff,0x9c,0x84,0xe2,
0xff,0xf7,0xef,0xe2,0xff,0x7b,0x52,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xff,0xbd,0xa5,0xe2,0xff,0xad,0x94,0xe2,
0xff,0x4a,0x18,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xff,0x94,0x7b,0xe2,
0xff,0xbd,0xa5,0xe2,0xff,0x52,0x21,0xe2,
0xf7,0x39,0x08,0xe1,0xf7,0x39,0x08,0xdf,
0xf7,0x39,0x08,0xd7,0xf7,0x39,0x08,0xc8,
0xf7,0x39,0x08,0xad,0xf7,0x39,0x08,0x86,
0xf7,0x39,0x08,0x90,0xf7,0x39,0x08,0xba,
0xf7,0x39,0x08,0xd7,0xf7,0x39,0x08,0xe8,
0xf7,0x39,0x08,0xef,0xf7,0x39,0x08,0xf2,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xff,0x4a,0x18,0xf3,0xff,0x9c,0x84,0xf3,
0xff,0xf7,0xef,0xf3,0xff,0xff,0xff,0xf3,
0xff,0xf7,0xef,0xf3,0xff,0xf7,0xef,0xf3,
0xff,0xde,0xd6,0xf3,0xff,0xad,0x94,0xf3,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xff,0x52,0x21,0xf3,0xff,0xbd,0xa5,0xf3,
0xff,0xf7,0xef,0xf3,0xff,0xff,0xff,0xf3,
0xff,0xff,0xff,0xf3,0xff,0xde,0xd6,0xf3,
0xff,0x94,0x7b,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xff,0xd6,0xc6,0xf3,
0xff,0xff,0xff,0xf3,0xff,0xde,0xd6,0xf3,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xff,0x5a,0x31,0xf3,
0xff,0xff,0xff,0xf3,0xff,0xff,0xff,0xf3,
0xff,0x73,0x4a,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xff,0x94,0x7b,0xf3,
0xff,0x9c,0x84,0xf3,0xff,0xad,0x94,0xf3,
0xff,0xbd,0xa5,0xf3,0xff,0xbd,0xa5,0xf3,
0xff,0x7b,0x52,0xf3,0xf7,0x39,0x08,0xf3,
0xff,0x4a,0x18,0xf3,0xff,0xff,0xff,0xf3,
0xff,0xff,0xff,0xf3,0xff,0x5a,0x31,0xf3,
0xf7,0x39,0x08,0xf2,0xf7,0x39,0x08,0xef,
0xf7,0x39,0x08,0xe8,0xf7,0x39,0x08,0xd7,
0xf7,0x39,0x08,0xba,0xf7,0x39,0x08,0x90,
0xf7,0x39,0x08,0x95,0xf7,0x39,0x08,0xc0,
0xf7,0x39,0x08,0xde,0xf7,0x39,0x08,0xef,
0xf7,0x39,0x08,0xf7,0xf7,0x39,0x08,0xfa,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xfb,0xff,0x5a,0x31,0xfb,
0xff,0xf7,0xef,0xfb,0xff,0xff,0xff,0xfb,
0xff,0xff,0xff,0xfb,0xff,0xff,0xff,0xfb,
0xff,0xff,0xff,0xfb,0xff,0xff,0xff,0xfb,
0xff,0xff,0xff,0xfb,0xff,0xbd,0xa5,0xfb,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xfb,0xff,0x7b,0x52,0xfb,
0xff,0xf7,0xef,0xfb,0xff,0xff,0xff,0xfb,
0xff,0xff,0xff,0xfb,0xff,0xff,0xff,0xfb,
0xff,0xff,0xff,0xfb,0xff,0xff,0xff,0xfb,
0xff,0xff,0xff,0xfb,0xff,0xd6,0xc6,0xfb,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xfb,0xff,0x73,0x4a,0xfb,
0xff,0xff,0xff,0xfb,0xff,0xff,0xff,0xfb,
0xff,0x8c,0x6b,0xfb,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xfb,0xff,0xbd,0xa5,0xfb,
0xff,0xff,0xff,0xfb,0xff,0xde,0xd6,0xfb,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfb,
0xff,0x52,0x21,0xfb,0xff,0xff,0xff,0xfb,
0xff,0xff,0xff,0xfb,0xff,0xff,0xff,0xfb,
0xff,0xff,0xff,0xfb,0xff,0xff,0xff,0xfb,
0xff,0xad,0x94,0xfb,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xfb,0xff,0x9c,0x84,0xfb,
0xff,0x9c,0x84,0xfb,0xff,0x4a,0x18,0xfb,
0xf7,0x39,0x08,0xfa,0xf7,0x39,0x08,0xf7,
0xf7,0x39,0x08,0xef,0xf7,0x39,0x08,0xde,
0xf7,0x39,0x08,0xc0,0xf7,0x39,0x08,0x95,
0xf7,0x39,0x08,0x96,0xf7,0x39,0x08,0xc2,
0xf7,0x39,0x08,0xe1,0xf7,0x39,0x08,0xf2,
0xf7,0x39,0x08,0xfa,0xf7,0x39,0x08,0xfd,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfe,
0xf7,0x39,0x08,0xfe,0xff,0xd6,0xc6,0xfe,
0xff,0xff,0xff,0xfe,0xff,0xf7,0xef,0xfe,
0xff,0x8c,0x6b,0xfe,0xff,0x4a,0x18,0xfe,
0xf7,0x39,0x08,0xfe,0xff,0xad,0x94,0xfe,
0xff,0xff,0xff,0xfe,0xff,0xbd,0xa5,0xfe,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfe,
0xff,0x52,0x21,0xfe,0xff,0xf7,0xef,0xfe,
0xff,0xff,0xff,0xfe,0xff,0xde,0xd6,0xfe,
0xff,0x7b,0x52,0xfe,0xff,0x4a,0x18,0xfe,
0xff,0x4a,0x18,0xfe,0xff,0x9c,0x84,0xfe,
0xff,0xff,0xff,0xfe,0xff,0xff,0xff,0xfe,
0xff,0x9c,0x84,0xfe,0xf7,0x39,0x08,0xfe,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfe,
0xff,0xd6,0xc6,0xfe,0xff,0xff,0xff,0xfe,
0xff,0xf7,0xef,0xfe,0xff,0xbd,0xa5,0xfe,
0xff,0x9c,0x84,0xfe,0xff,0x8c,0x6b,0xfe,
0xff,0x73,0x4a,0xfe,0xff,0xff,0xff,0xfe,
0xff,0xff,0xff,0xfe,0xff,0x7b,0x52,0xfe,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfe,
0xff,0x52,0x21,0xfe,0xff,0xff,0xff,0xfe,
0xff,0xff,0xff,0xfe,0xff,0x9c,0x84,0xfe,
0xff,0x94,0x7b,0xfe,0xff,0x8c,0x6b,0xfe,
0xff,0x5a,0x31,0xfe,0xf7,0x39,0x08,0xfe,
0xff,0x52,0x21,0xfe,0xff,0xde,0xd6,0xfe,
0xff,0xde,0xd6,0xfe,0xff,0x4a,0x18,0xfe,
0xf7,0x39,0x08,0xfd,0xf7,0x39,0x08,0xfa,
0xf7,0x39,0x08,0xf2,0xf7,0x39,0x08,0xe1,
0xf7,0x39,0x08,0xc2,0xf7,0x39,0x08,0x96,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfe,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xff,0xf7,0xef,0xff,
0xff,0xff,0xff,0xff,0xff,0x7b,0x52,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xff,0xad,0x94,0xff,
0xff,0xff,0xff,0xff,0xff,0xd6,0xc6,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xff,0xbd,0xa5,0xff,0xff,0xff,0xff,0xff,
0xff,0xf7,0xef,0xff,0xff,0x4a,0x18,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xff,0xad,0x94,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xff,0x7b,0x52,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xde,0xd6,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xff,0x5a,0x31,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xff,0x5a,0x31,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfe,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xff,0xde,0xd6,0xff,
0xff,0xff,0xff,0xff,0xff,0xd6,0xc6,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xff,0xad,0x94,0xff,
0xff,0xff,0xff,0xff,0xff,0xbd,0xa5,0xff,
0xf7,0x39,0x08,0xff,0xff,0x4a,0x18,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0x8c,0x6b,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xff,0x5a,0x31,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0x4a,0x18,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xff,0xde,0xd6,0xff,
0xff,0xff,0xff,0xff,0xff,0xf7,0xef,0xff,
0xff,0xbd,0xa5,0xff,0xff,0xd6,0xc6,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0x8c,0x6b,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xff,0x73,0x4a,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xff,0x73,0x4a,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfe,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xff,0x8c,0x6b,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0x9c,0x84,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xff,0x5a,0x31,0xff,
0xff,0x7b,0x52,0xff,0xff,0x5a,0x31,0xff,
0xf7,0x39,0x08,0xff,0xff,0x73,0x4a,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xff,0x8c,0x6b,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xff,0x8c,0x6b,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0x5a,0x31,0xff,0xff,0x94,0x7b,0xff,
0xff,0xff,0xff,0xff,0xff,0xf7,0xef,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xff,0x7b,0x52,0xff,0xff,0xff,0xff,0xff,
0xff,0xf7,0xef,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xff,0x7b,0x52,0xff,0xff,0xff,0xff,0xff,
0xff,0xf7,0xef,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfe,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xff,0xbd,0xa5,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0x94,0x7b,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xff,0x73,0x4a,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0x52,0x21,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xff,0xde,0xd6,0xff,0xff,0xff,0xff,0xff,
0xff,0xbd,0xa5,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xff,0x4a,0x18,0xff,
0xff,0xf7,0xef,0xff,0xff,0xff,0xff,0xff,
0xff,0xbd,0xa5,0xff,0xff,0xf7,0xef,0xff,
0xff,0xff,0xff,0xff,0xff,0x94,0x7b,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xff,0x8c,0x6b,0xff,0xff,0xff,0xff,0xff,
0xff,0xde,0xd6,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xff,0xf7,0x39,0x08,0xff,
0xff,0x7b,0x52,0xff,0xff,0xff,0xff,0xff,
0xff,0xf7,0xef,0xff,0xf7,0x39,0x08,0xff,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x96,0xf7,0x39,0x08,0xc2,
0xf7,0x39,0x08,0xe1,0xf7,0x39,0x08,0xf2,
0xf7,0x39,0x08,0xfa,0xf7,0x39,0x08,0xfd,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfe,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfe,
0xf7,0x39,0x08,0xfe,0xff,0xd6,0xc6,0xfe,
0xff,0xf7,0xef,0xfe,0xff,0xff,0xff,0xfe,
0xff,0x94,0x7b,0xfe,0xf7,0x39,0x08,0xfe,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfe,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfe,
0xff,0xf7,0xef,0xfe,0xff,0xff,0xff,0xfe,
0xff,0xde,0xd6,0xfe,0xff,0x4a,0x18,0xfe,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfe,
0xf7,0x39,0x08,0xfe,0xff,0x5a,0x31,0xfe,
0xff,0xff,0xff,0xfe,0xff,0xff,0xff,0xfe,
0xff,0x73,0x4a,0xfe,0xf7,0x39,0x08,0xfe,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfe,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfe,
0xff,0xbd,0xa5,0xfe,0xff,0xff,0xff,0xfe,
0xff,0xff,0xff,0xfe,0xff,0xff,0xff,0xfe,
0xff,0xf7,0xef,0xfe,0xff,0x4a,0x18,0xfe,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfe,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfe,
0xff,0x94,0x7b,0xfe,0xff,0xff,0xff,0xfe,
0xff,0xd6,0xc6,0xfe,0xf7,0x39,0x08,0xfe,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfe,
0xf7,0x39,0x08,0xfe,0xf7,0x39,0x08,0xfe,
0xff,0x8c,0x6b,0xfe,0xff,0xff,0xff,0xfe,
0xff,0xde,0xd6,0xfe,0xf7,0x39,0x08,0xfe,
0xf7,0x39,0x08,0xfd,0xf7,0x39,0x08,0xfa,
0xf7,0x39,0x08,0xf2,0xf7,0x39,0x08,0xe1,
0xf7,0x39,0x08,0xc2,0xf7,0x39,0x08,0x96,
0xf7,0x39,0x08,0x95,0xf7,0x39,0x08,0xc0,
0xf7,0x39,0x08,0xde,0xf7,0x39,0x08,0xef,
0xf7,0x39,0x08,0xf7,0xf7,0x39,0x08,0xfa,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfb,
0xff,0xd6,0xc6,0xfb,0xff,0xff,0xff,0xfb,
0xff,0xff,0xff,0xfb,0xff,0xd6,0xc6,0xfb,
0xff,0x4a,0x18,0xfb,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfb,
0xff,0x73,0x4a,0xfb,0xff,0xff,0xff,0xfb,
0xff,0xff,0xff,0xfb,0xff,0xf7,0xef,0xfb,
0xff,0xad,0x94,0xfb,0xff,0x73,0x4a,0xfb,
0xff,0x8c,0x6b,0xfb,0xff,0xff,0xff,0xfb,
0xff,0xff,0xff,0xfb,0xff,0xd6,0xc6,0xfb,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfb,
0xff,0x5a,0x31,0xfb,0xff,0xff,0xff,0xfb,
0xff,0xff,0xff,0xfb,0xff,0xff,0xff,0xfb,
0xff,0xad,0x94,0xfb,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfb,
0xff,0x9c,0x84,0xfb,0xff,0xff,0xff,0xfb,
0xff,0xd6,0xc6,0xfb,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xfb,0xf7,0x39,0x08,0xfb,
0xff,0x94,0x7b,0xfb,0xff,0xff,0xff,0xfb,
0xff,0xde,0xd6,0xfb,0xf7,0x39,0x08,0xfb,
0xf7,0x39,0x08,0xfa,0xf7,0x39,0x08,0xf7,
0xf7,0x39,0x08,0xef,0xf7,0x39,0x08,0xde,
0xf7,0x39,0x08,0xc0,0xf7,0x39,0x08,0x95,
0xf7,0x39,0x08,0x90,0xf7,0x39,0x08,0xba,
0xf7,0x39,0x08,0xd7,0xf7,0x39,0x08,0xe8,
0xf7,0x39,0x08,0xef,0xf7,0x39,0x08,0xf2,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xff,0x8c,0x6b,0xf3,
0xff,0xff,0xff,0xf3,0xff,0xff,0xff,0xf3,
0xff,0xbd,0xa5,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xff,0x73,0x4a,0xf3,
0xff,0xde,0xd6,0xf3,0xff,0xff,0xff,0xf3,
0xff,0xff,0xff,0xf3,0xff,0xff,0xff,0xf3,
0xff,0xff,0xff,0xf3,0xff,0xff,0xff,0xf3,
0xff,0xde,0xd6,0xf3,0xff,0x4a,0x18,0xf3,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xff,0xd6,0xc6,0xf3,
0xff,0xff,0xff,0xf3,0xff,0xf7,0xef,0xf3,
0xff,0x4a,0x18,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xff,0xad,0x94,0xf3,0xff,0xff,0xff,0xf3,
0xff,0xbd,0xa5,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf3,0xf7,0x39,0x08,0xf3,
0xff,0x94,0x7b,0xf3,0xff,0xff,0xff,0xf3,
0xff,0xd6,0xc6,0xf3,0xf7,0x39,0x08,0xf3,
0xf7,0x39,0x08,0xf2,0xf7,0x39,0x08,0xef,
0xf7,0x39,0x08,0xe8,0xf7,0x39,0x08,0xd7,
0xf7,0x39,0x08,0xba,0xf7,0x39,0x08,0x90,
0xf7,0x39,0x08,0x86,0xf7,0x39,0x08,0xad,
0xf7,0x39,0x08,0xc8,0xf7,0x39,0x08,0xd7,
0xf7,0x39,0x08,0xdf,0xf7,0x39,0x08,0xe1,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xff,0x5a,0x31,0xe2,0xff,0xd6,0xc6,0xe2,
0xff,0x73,0x4a,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xff,0x7b,0x52,0xe2,
0xff,0xbd,0xa5,0xe2,0xff,0xd6,0xc6,0xe2,
0xff,0xd6,0xc6,0xe2,0xff,0x94,0x7b,0xe2,
0xff,0x4a,0x18,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xff,0x73,0x4a,0xe2,
0xff,0xad,0x94,0xe2,0xff,0x5a,0x31,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xff,0x52,0x21,0xe2,0xff,0x5a,0x31,0xe2,
0xff,0x4a,0x18,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe2,0xf7,0x39,0x08,0xe2,
0xff,0x9c,0x84,0xe2,0xff,0xff,0xff,0xe2,
0xff,0xd6,0xc6,0xe2,0xf7,0x39,0x08,0xe2,
0xf7,0x39,0x08,0xe1,0xf7,0x39,0x08,0xdf,
0xf7,0x39,0x08,0xd7,0xf7,0x39,0x08,0xc8,
0xf7,0x39,0x08,0xad,0xf7,0x39,0x08,0x86,
0xf7,0x39,0x08,0x74,0xf7,0x39,0x08,0x95,
0xf7,0x39,0x08,0xad,0xf7,0x39,0x08,0xba,
0xf7,0x39,0x08,0xc0,0xf7,0x39,0x08,0xc2,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc3,0xf7,0x39,0x08,0xc3,
0xff,0x4a,0x18,0xc3,0xff,0x73,0x4a,0xc3,
0xff,0x5a,0x31,0xc3,0xf7,0x39,0x08,0xc3,
0xf7,0x39,0x08,0xc2,0xf7,0x39,0x08,0xc0,
0xf7,0x39,0x08,0xba,0xf7,0x39,0x08,0xad,
0xf7,0x39,0x08,0x95,0xf7,0x39,0x08,0x74,
0xf7,0x39,0x08,0x5a,0xf7,0x39,0x08,0x74,
0xf7,0x39,0x08,0x86,0xf7,0x39,0x08,0x90,
0xf7,0x39,0x08,0x95,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x97,
0xf7,0x39,0x08,0x97,0xf7,0x39,0x08,0x95,
0xf7,0x39,0x08,0x90,0xf7,0x39,0x08,0x86,
0xf7,0x39,0x08,0x74,0xf7,0x39,0x08,0x5a,
};

static Gfx _goal_aligner1[] = { gsSPEndDisplayList() };

/* ============================================================
          Vtx
 ============================================================ */
static Vtx vtx_Shape_of___POLYHEDRON_1052_[] = {
  {  -300,   300,     0,0, 0x0000,0x0400, 0xff,0xff,0xff,0xff }, /*     0 */
  {   300,     0,     0,0, 0x1000,0x0000, 0xff,0xff,0xff,0xff }, /*     1 */
  {   300,   300,     0,0, 0x1000,0x0400, 0xff,0xff,0xff,0xff }, /*     2 */
  {  -300,   300,     0,0, 0x0000,0x0400, 0xff,0xff,0xff,0xff }, /*     3 */
  {  -300,     0,     0,0, 0x0000,0x0000, 0xff,0xff,0xff,0xff }, /*     4 */
  {   300,     0,     0,0, 0x1000,0x0000, 0xff,0xff,0xff,0xff }, /*     5 */
};

/* ============================================================
          Gfx
 ============================================================ */
static Gfx gfx_Shape_of___POLYHEDRON_1052_[] = {
  gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF),
  gsSPSetGeometryMode( G_SHADE|G_SHADING_SMOOTH ),
  gsDPSetCombineLERP(1, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, 1, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0),
  gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
  gsDPSetTextureLUT( G_TT_NONE ),
  gsDPLoadMultiBlock( SEGADRS(6,0), 0, 0,
    G_IM_FMT_RGBA, G_IM_SIZ_32b, 64, 16, 0,
    2, 2, 6, 4, 0, 0 ),
  gsSPVertex( SEGADRS(5, 0), 6, 0 ),
  gsSP2Triangles(  0,  1,  2,  0,  3,  4,  5,  0),
  gsSPEndDisplayList(),
};

/* ============================================================
          Shape Structure
 ============================================================ */
static NDR_SHAPE shape_Shape_of___POLYHEDRON_1052_ = {
  gfx_Shape_of___POLYHEDRON_1052_,
  vtx_Shape_of___POLYHEDRON_1052_, 6, 5,
  bmp_goal,
  NULL,
  6, 7,
  NULL,
  NULL,
  NULL,
  NULL
};

/* ============================================================
          Object Structure Area
 ============================================================ */
/* Object #0 */
static NDR_OBJ _dummy_obj={
  NDC_TYPE_NULL, 0, 0x00000000,
  {0,0,0, 0,0,0, 1,1,1},
  -1,
  0x0000, 0x00000000, 0x00000000, 0x00000000,
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  -1, 0, 0, 0x010203,
  {-1, -1}, 0, NULL
};

/* Object #1 */
u16 _goal_XLU_Group_link[]={ 1 };
static NDR_OBJ _goal_XLU_Group={
  NDC_TYPE_NULL, 0, 0x00000000,
  {0.000000,0.000000,0.000000,
   0.000000,0.000000,0.000000,
   1.000000,1.000000,1.000000},
  -1,
  0x0000, 0x00000000, 0x00000000, 0x00000000,
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  -1, 0, 0, 0x010203,
  {-1, -1}, 1, _goal_XLU_Group_link
};

/* Object #2 */
static NDR_OBJ _goal_XLU={
  NDC_TYPE_3D, 0, 0x500 + 0x00,
  {0.000000,0.000000,0.000000,
   0.000000,0.000000,0.000000,
   1.000000,1.000000,1.000000},
  0,
  0x0000, 0x00000001, 0xd6600404, 0x00000000,
  {0x0f,0x0f,0x0f,0x04,0x0f,0x0f,0x0f,0x04},
  {0x0f,0x0f,0x0f,0x04,0x0f,0x0f,0x0f,0x04},
  -1, 0, 0, 0x010203,
  {-1, -1}, 0, NULL
};

/* Object #3 */
static NDR_OBJ _NULL_OBJECT_1={
  NDC_TYPE_NULL, 0, 0x00000000,
  {0,0,0, 0,0,0, 1,1,1},
  -1,
  0x0000, 0x00000000, 0x00000000, 0x00000000,
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  -1, 0, 0, 0x010203,
  {-1, -1}, 0, NULL
};

/* Object #4 */
static NDR_OBJ _NULL_OBJECT_2={
  NDC_TYPE_NULL, 0, 0x00000000,
  {0,0,0, 0,0,0, 1,1,1},
  -1,
  0x0000, 0x00000000, 0x00000000, 0x00000000,
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  -1, 0, 0, 0x010203,
  {-1, -1}, 0, NULL
};

/* Object #5 */
static NDR_OBJ _NULL_OBJECT_3={
  NDC_TYPE_NULL, 0, 0x00000000,
  {0,0,0, 0,0,0, 1,1,1},
  -1,
  0x0000, 0x00000000, 0x00000000, 0x00000000,
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  -1, 0, 0, 0x010203,
  {-1, -1}, 0, NULL
};

/* ============================================================
          Scene Structure Area
 ============================================================ */
static NDR_SCN_INST_OBJ goal_XLU_Group_scene_instlist[]={
 {
  {0,0,0, 0,0,0, 1,1,1},
  3 /* NULL_OBJECT_1 */
 },
 {
  {0,0,0, 0,0,0, 1,1,1},
  5 /* NULL_OBJECT_3 */
 },
 {
  {0,0,0, 0,0,0, 1,1,1},
  4 /* NULL_OBJECT_2 */
 },
 {
  {0.000000,0.000000,0.000000,
   0.000000,0.000000,0.000000,
   1.000000,1.000000,1.000000},
  1 /* goal_XLU_Group */
 },
};

static NDR_SCN_LIGHT _goal_XLU_Group_scene_light[]={
  { 0, 0xfefefeff,
    0.000000, 1.000000, 0.000000, 0,0 },
};

static NDR_SCENE goal_XLU_Group_scene={
  {950.000000, 1000.000000, 0x4c, 0x4c, 0x4c, 0xff},
  {1, 45.841393, 1.333330, 1.000000, 0, 0, 0, 0, 1, 10000, 0, 1, 2},
  { 0x000000ff, 1, _goal_XLU_Group_scene_light },
  0x0000, 0xfffc,
  goal_XLU_Group_scene_instlist, 4,
};

/* ============================================================
          Shape Structure List
 ============================================================ */
static NDR_SHAPE *shapelist_goal[] = {
  &shape_Shape_of___POLYHEDRON_1052_,
};

/* ============================================================
          Object Struct List
 ============================================================ */
static NDR_OBJ *objlist_goal[]={
  &_dummy_obj, /* 0 */
  &_goal_XLU_Group, /* 1 */
  &_goal_XLU, /* 2 */
  &_NULL_OBJECT_1, /* 3 */
  &_NULL_OBJECT_2, /* 4 */
  &_NULL_OBJECT_3, /* 5 */
};

/* ############################################################
          Resource Information
 ############################################################ */
NDR_RESINFO resinfo_goal={
  &goal_XLU_Group_scene,
  20.000000,
  objlist_goal,
  shapelist_goal,
  NULL,
  NULL,
  NULL,
  NULL,
  6, 1, 0, 0, 0, 0
};

