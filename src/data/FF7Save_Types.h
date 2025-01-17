//    SPDX-FileCopyrightText: 2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#ifdef _MSC_VER
#   define PACK(structure)          \
    __pragma(pack(push, 1))     \
    structure                   \
    __pragma(pack(pop))
#elif defined(__MINGW32__)
#define PACK(structure) structure __attribute__ ((gcc_struct, __packed__))
#else
#define PACK(structure) structure Q_PACKED
#endif

#include <QVector>
#include <ff7tkdata_export.h>
#include <Type_FF7CHAR>
#include <Type_FF7CHOCOBO>
//Materia Type is included as part of FF7Char
/*~~~~~~~~~~~~~~~~~~~~~~~~STRUCT TYPES AND SAVE STRUCT~~~~~~~~~~~~~~~~*/
PACK(
struct FF7TKDATA_EXPORT LOVE {
    qint8 aeris;
    qint8 tifa;
    qint8 yuffie;
    qint8 barret;
});

/*! \struct FF7DESC
 *  \brief Description of savegame used for previews
 *
 *  68 Bytes total size All known
 */
PACK(
struct FF7TKDATA_EXPORT FF7DESC {
    quint8 level;       /**< [0x0000] Lead character's level*/
    qint8 party[3];     /**< [0x0001] Party*/
    quint8 name[16];    /**< [0x0004] Lead character's name (ff7 string)*/
    quint16 curHP;      /**< [0x0014] Lead character's current HP*/
    quint16 maxHP;      /**< [0x0016] Lead character's base HP*/
    quint16 curMP;      /**< [0x0018] Lead character's current MP*/
    quint16 maxMP;      /**< [0x001A] Lead character's base MP*/
    quint32 gil;        /**< [0x001C] Amount of gil*/
    quint32 time;       /**< [0x0020] Total number of seconds played*/
    quint8 location[32];/**< [0x0024] Save location (ff7 string)*/
});
PACK(
struct FF7TKDATA_EXPORT FF7XYT {// size of 7. used for coords
    qint16 x;
    qint16 y;
    quint16 t;
    quint8 d;
});

/*! \struct FF7SLOT
 *  \brief Main FF7 Save Data Structure
 *
 * 4340 Bytes total size.  Most known  alot still unknown
 * \todo merge FF7FieldItemList offset data when possible.
 * \todo Discover more bytes then before
 */
PACK(
struct FF7TKDATA_EXPORT FF7SLOT {
    quint16 checksum;           /**< [0x0000] Checksum */
    quint8 z_1[2];              /**< [0x0002] UNKNOWN DATA*/
    FF7DESC desc;               /**< [0x0004] Length:0x44] Slot description*/
    quint8 colors[4][3];        /**< [0x0048] Window colors (RGB)*/
    FF7CHAR chars[9];           /**< [0x0054:84] The nine characters (Cl,Ba,Ti,Ae,Re,Yu,Ca,Vi,Ci)*/
    qint8 party[3];             /**< [0x04F8] Party members*/
    quint8 z_2[1];              /**< [0x04FB] always 0xFF*/
    quint16 items[320];         /**< [0x04FC] Items (320 slots)*/
    materia materias[200];      /**< [0x077C] Materia (200 slots)*/
    materia stolen[48];         /**< [0x0A9C] materia stolen by yuffie.*/
    quint8 z_3[32];             /**< [0x0B5C] UNKNOWN DATA (Always 0xFF?)*/
    quint32 gil;                /**< [0x0B7C] Party gil*/
    quint32 time;               /**< [0x0B80] Total number of seconds played*/
    quint8 timer[3];            /**< [0x0B84] countdown timer H:M:S*/
    quint8 z_4[13];             /**< [0x0B87] UNKNOWN DATA*/
    quint16 mapid;              /**< [0x0B94] Current map*/
    quint16 locationid;         /**< [0x0B96] Current location*/
    quint8 z_5[2];              /**< [0x0B98] UNKNOWN DATA*/
    FF7XYT coord;               /**< [0x0B9A] Current coordinates (world map)*/
    quint8 z_6[3];              /**< [0x0BA0] UNKNOWN DATA*/
    quint16 mprogress;          /**< [0x0BA4] Main Progress var*/
    quint8 z_7[1];              /**< [0x0BA6] UNKNOWN DATA*/
    LOVE love;                  /**< [0X0BA7] Main love points.*/
    quint8 z_8[17];             /**< [0x0BAB] UNKNOWN DATA*/
    quint16 battles;            /**< [0x0BBC] Number of battle*/
    quint16 runs;               /**< [0x0BBE] Number of escapes*/
    quint16 menu_visible;       /**< [0x0BC0] Menu items Visible*/
    quint16 menu_locked;        /**< [0x0BC2] Menu items locked*/
    quint8 z_9[16];             /**< [0x0BC4] UNKNOWN DATA*/
    quint8 itemsmask_1;         /**< [0x0BD4] Item mask_1*/
    quint8 materiacaves;        /**< [0x0BD5] materia caves picked up  0x01 mime,0x02 HP<->MP,0x04 4xmag, 0x08 KOTR*/
    quint8 z_10[14];            /**< [0x0BD6] UNKNOWN DATA*/
    quint8 keyitems[8];         /**< [0x0BE4] Key items*/
    quint8 z_11[8];             /**< [0x0BEC] UNKNOWN DATA*/
    LOVE b_love;                /**< [0x0BF4] Battle Love Points*/
    quint8 z_12[1];             /**< [0x0BF8] UNKNOWN DATA*/
    qint8 pennedchocos[4];      /**< [0x0BF9] chocos in fenced area at farm rating*/
    quint8 z_13[2];             /**< [0x0BFD] UNKNOWN DATA*/
    quint8 u_weapon_hp[3];      /**< [0x0BFF] Ultimate Weapons Remaining Hp*/
    quint8 seenpandora;         /**< [0x0C02] bit 0: seen pandoras box. more data on other bits?*/
    quint8 z_14[27];            /**< [0x0C03] UNKNOWN DATA*/
    quint8 tut_sub;             /**< [0x0C1E] Have we seen the sub tutorial 0x04 =on Show Battle Targets Label 0x40=on*/
    quint8 ruby_emerald;        /**< [0x0C1F] WEAPONS ALIVE? 0x05=both 0x1D =non 0x0D = emerald*/
    quint8 z_15[2];             /**< [0x0C20] UNKNOWN DATA*/
    quint8 world_map_chocobos;  /**< [0x0C22] what is chocobos are visible on world map*/
    quint8 world_map_vehicles;  /**< [0x0C23] what is vehicles are visible on world map 0x00 empty,0x01 buggy,0x04 tiny bronco,0x10 highwind (combineable; never 0x11)*/
    quint8 z_16[38];            /**< [0x0C24] UNKNOWN DATA*/
    quint8 condorlosses;        /**< [0x0C4A] Number of losses in condor game*/
    quint8 condorwins;          /**< [0x0C4B] Number of wins in condor game*/
    quint8 z_17[12];            /**< [0X0C4C] UNKNOWN DATA*/
    quint16 condorfunds;        /**< [0x0C58] Funds for condor game*/
    quint8 z_18[43];            /**< [0x0C5A] UNKNOWN DATA*/
    quint8 bm_progress1;        /**< [0x0C85] Bombing Mission Flag 1*/
    quint8 bm_progress2;        /**< [0x0C86] Bombing Mission Flag 2*/
    quint8 z_19[38];            /**< [0X0C87] UNKNOWN DATA 45 50*/
    quint8 f_party[3];          /**< [0X0CAD] Party Members on Field */
    quint8 z_20[4];             /**< [0X0CB0] UNKNOWN DATA */
    quint8 aeris_church;        /**< [0x0CB4] aeris church*/
    quint8 z_21[49];            /**< [0x0CB5] UNKNOWN DATA*/
    quint8 bm_progress3;        /**< [0X0CE6] Bombing mission flag 3*/
    quint8 z_22[7];             /**< [0X0CE7] UNKNOWN DATA*/
    quint16 gp;                 /**< [0x0CEE] Party GP (0-10000)*/
    quint8 z_23[4];             /**< [0x0CF0] UNKNOWN DATA*/
    quint16 battlepoints;       /**< [0x0CF4] Battle Points*/
    quint8 z_24[6];             /**< [0x0CF6] UNKNOWN DATA*/
    qint8 stables;              /**< [0x0CFC] Number of chocobo stables owned*/
    qint8 stablesoccupied;      /**< [0x0CFD] Number of occupied stables*/
    quint8 z_25[1];             /**< [0x0CFE] UNKNOWN DATA*/
    qint8 chocobomask;          /**< [0x0CFF] Mask of occupied stables*/
    quint8 chocomated;          /**< [0x0D00] what stalls can't mate*/
    quint8 z_26[40];            /**< [0x0D01] UNKNOWN DATA*/
    quint8 yuffieforest;        /**< [0x0D29] yuffie in forest if bit1 = 1 then yes.. others here too?*/
    quint8 z_27[28];            /**< [0x0D2A] UNKNOWN DATA*/
    quint8 donprogress;         /**< [0x0D46] don's progress var. 00 - 03 when done*/
    quint8 z_28[31];            /**< [0x0D47] UNKNOWN DATA*/
    quint8 turtleflyers;        /**< [0x0D66] turtles paradice flyers.*/
    quint8 z_29[12];            /**< [0X0D67] UNKNOWN DATA*/
    quint8 reg_yuffie;          /**< [0x0D73] yuffie regular? 0x6F=yes 0x6E=no*/
    quint8 z_30[15];            /**< [0x0D74] UNKNOWN DATA*/
    quint8 midgartrainflags;    /**< [0x0D83] Midgar Train Flags.*/
    quint8 z_31[64];            /**< [0x0D84] UNKNOWN DATA*/
    FF7CHOCOBO chocobos[4];     /**< [0x0DC4] Chocobo slots*/
    quint8 z_32[13];            /**< [0x0E04] UNKNOWN DATA*/
    quint16 BikeHighScore;      /**< [0x0E11] Bike Mini Game High Score*/
    quint8 SnowUnused;          /**< [0x0E13] Unused var for snowboard game?*/
    quint32 SnowBegFastTime;    /**< [0x0E14] Fastest Time For Snowboard Beginner Course stored in Msec 3bytes byte[0] unused*/
    quint32 SnowExpFastTime;    /**< [0x0E16] Fastest Time For Snowboard Expert Course Stored in Msec 3bytes byte[0] unused*/
    quint32 SnowCrazyFastTime;  /**< [0x0E1C] Fastest Time For Snowboard Crazy Course Stored in Msec 3bytes byte[0] unused*/ quint8 SnowBegScore;       /**< [0x0E20] SnowBoard Minigame HighScore For Beginner Course*/
    quint8 SnowExpScore;        /**< [0x0E21] SnowBoard Minigame HighScore For Expert Course*/
    quint8 SnowCrazyScore;      /**< [0x0E22] SnowBoard Minigame HighScore For Crazy Course*/
    quint8 Snowtempvar;         /**< [0x0E23] SnowBoard Minigame Temp var Not used.*/
    quint16 coster_2;           /**< [0x0E24] Coster 2nd place score*/
    quint16 coster_3;           /**< [0x0E26] Coster 3rd place score*/
    quint8 z_33[17];            /**< [0x0E28] UNKNOWN DATA*/
    quint16 coster_1;           /**< [0x0E39] Coster 1st place*/
    quint8 z_34[3];             /**< [0x0E3B] UNKNOWN DATA*/
    quint8 stablechocorating[6];/**< [0x0E3E] Choco Billy's Rating for chocobo in stable 1-6 (same ranks as penned)*/
    quint8 z_35[24];            /**< [0x0E44] UNKNOWN DATA*/
    qint16 cratersaveMapId;     /**< [0x0E5C] Map id of location the portable save is on*/
    qint16 cratersaveX;         /**< [0x0E5E] X coord of portable save*/
    qint16 cratersaveY;         /**< [0x0E60] Y coord of portable save*/
    qint16 cratersaveZ;         /**< [0x0E62] Z coord of portable save*/
    quint8 z_36[64];            /**< [0x0E64] UNKNOWN DATA*/
    qint8 disc;                 /**< [0x0EA4] Current CD*/
    quint8 z_37[1];             /**< [0x0EA5] UNKNOWN DATA*/
    quint8 intbombing;          /**< [0x0EA6] 0x14 On Start of Bombing Mission , 0x56 On first Save..*/
    quint8 z_38[3];             /**< [0x0EA7] UNKNOWN DATA*/
    quint16 steps;              /**< [0x0EAA] Number of steps used in glacear to make you pass out @ 544 steps*/
    quint8 z_39[22];            /**< [0x0EAC] UNKNOWN DATA*/
    quint8 field_help;          /**< [0x0EC2] Show field hand 1=on 0=off*/
    quint8 z_40[1];             /**< [0x0EC3] UNKNOWN DATA*/
    quint8 chocobonames[6][6];  /**< [0x0EC4] <-OK Chocobo names*/
    quint16 chocostaminas[6];   /**< [0x0EE8] Chocobo staminas 12 bytes*/
    quint8 reg_vinny;           /**< [0x0EF4] 0xFF for true 0xFB false (vincent a regualar?)*/
    quint8 z_41[23];            /**< [0x0EF5] UNKNOWN DATA*/
    quint8 location[24];        /**< [0x0F0C] Location String*/
    quint8 z_42[5];             /**< [0x0F24] UNKNOWN DATA*/
    quint8 tut_save;            /**< [0x0F29] Have we seen save tut ? 0x3A true , 0x32 false*/
    quint8 z_43[14];            /**< [0x0F2A] UNKNOWN DATA*/
    quint8 wonsubgame;          /**< [0x0F38] 1 If you ahve won the sub mini game*/
    quint8 z_44[35];            /**< [0x0F39] UNKNOWN DATA*/
    quint32 l_world;            /**< [0x0F5C] coords of the leader on the world map part 1 (X, id, angle)*/
    quint32 l_world2;           /**< [0x0F60] leader coords part 2 (Y,Z)*/
    quint32 wc_world;           /**< [0x0F64] Caught Wild Chocobo coords part 1*/
    quint32 wc_world2;          /**< [0x0F68] Caught Wild Chocobo coords part 2*/
    quint32 tc_world;           /**< [0x0F6C] Tiny Bronco/Chocobo coords part 1*/
    quint32 tc_world2;          /**< [0x0F70] Tiny Bronco/Chocobo coords part 2*/
    quint32 bh_world;           /**< [0x0F74] Buggy/Highwind coords 1*/
    quint32 bh_world2;          /**< [0x0F78] Buggy/Highwind coords 2*/
    quint32 sub_world;          /**< [0x0F7C] Submarine on world part 1*/
    quint32 sub_world2;         /**< [0x0F80] Submarine on world part 2*/
    quint32 durw_world;         /**< [0x0F84] Diamond/Ultimate And Ruby Weapons Coords.*/
    quint32 durw_world2;        /**< [0x0F88] Diamond/Ultimate And Ruby Weapons Coords.*/
    quint16 pole1_x;            /**< [0x0F8C] 1st Snow Pole X Coordinate.*/
    quint16 pole1_y;            /**< [0x0F8E] 1st Snow Pole Y Coordinate.*/
    quint16 pole2_x;            /**< [0x0F90] 2nd Snow Pole X Coordinate.*/
    quint16 pole2_y;            /**< [0x0F92] 2nd Snow Pole Y Coordinate.*/
    quint16 pole3_x;            /**< [0x0F94] 3rd Snow Pole X Coordinate.*/
    quint16 pole3_y;            /**< [0x0F96] 3rd Snow Pole Y Coordinate.*/
    quint8 z_45[236];           /**< [0x0F98] UNKNOWN DATA*/
    FF7CHOCOBO choco56[2];      /**< [0x1084] Chocobo slots 5-6*/
    quint16 phsallowed;         /**< [0x10A4] who is allowed in the phs*/
    quint16 phsvisible;         /**< [0x10A6] who is visible in the phs*/
    quint8 z_46[48];            /**< [0x10A8] UNKNOWN DATA*/
    quint8 battlespeed;         /**< [0x10D8] Battle Speed*/
    quint8 battlemspeed;        /**< [0x10D9] Battle Message Speed*/
    quint16 options;            /**< [0x10DA] Options*/
    quint8 controller_map[16];  /**< [0x10DC] controller mapping (only used in psx save)*/
    quint8 fieldmspeed;         /**< [0x10EC] Message Speed On field*/
    quint8 z_47[8];             /**< [0x10ED] UNKNOWN DATA*/
});

PACK(
    /* FF7HEADFOOT FORMAT COMPATIBILITY (Vegeta_Ss4) v0.8.3*/
struct FF7TKDATA_EXPORT FF7HEADFOOT {
    quint8 sl_header[0x0200];   // [0x0000] Slot Header
    quint8 sl_footer[0x0D0C];   // [0x0000] Slot Footer
});

typedef QVector< QString > SubContainer;
