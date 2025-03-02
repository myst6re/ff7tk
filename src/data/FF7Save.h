//    SPDX-FileCopyrightText: 2012 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QObject>
#include <cstdlib>
#include <ff7tkdata_export.h>
#include <FF7SaveInfo>
#include <FF7Save_Types>

class QColor;
class QDateTime;
class QFile;
class QFileInfo;
class QDomDocument;
class QTextCodec;

/** \class FF7Save
 *  \todo Support for PS4 Saves.
 *  \todo Support for XBONE Saves
 *  \brief edit saves from Final Fantasy 7
 *
 *  FF7Save does it all. Open the file , edit then save. All of the file handling will be taken care of for you.
 *  the following are supported formats:
 *  | File   | Description
 *  |--------|-------------
 *  | *.ff7  |PC Format Save; If a metadata.xml file is in the save path it will be updated.
 *  |ff7slot*|Switch Format save, same as PC
 *  | *.mcr  |Common Emulator format (Virtual Memory Card)
 *  | *.mcd  |Common Emulator format (Virtual Memory Card)
 *  | *.mci  |Common Emulator format (Virtual Memory Card)
 *  | *.mc   |Common Emulator format (Virtual Memory Card)
 *  | *.ddf  |Common Emulator format (Virtual Memory Card)
 *  | *.ps   |Common Emulator format (Virtual Memory Card)
 *  | *.psm  |Common Emulator format (Virtual Memory Card)
 *  | *.bin  |Common Emulator format (Virtual Memory Card)
 *  | *.vgs  |Memory Card from Virtual Game Station
 *  | *.mem  |Memory Card from Virtual Game Station
 *  | *.gme  |Dex drive format virtual memory card
 *  | *.VM1  |Internal PSX Memory Card on PS3 (Virtual Memory Card)
 *  | *.VMP  |VMC format used by the PSP and PsVita
 *  | *.PSV  |Single save "Exported" by a PS3.
 *  |   *    |A Raw PSX memory card "file" extracted from a real or virtual memory card
 *  | *.mcs  |Psx Game Edit Save
 *  | *.ps1  |Memory Juggle Save
 *  | *.psx  |XP AR GS Caetla Save
 *  | *.mcb  |Smart Link format
 *  | *.mcx  | Dantel Format
 *  | *.pda  | Dantel Format
 */
class FF7TKDATA_EXPORT FF7Save: public QObject
{
    Q_OBJECT
public:
    //Enums
    enum WORLDVEHICLE {WVEHCILE_BUGGY = 0/**< 0*/, WVEHCILE_TBRONCO/**< 2*/ = 2, WVEHCILE_HIGHWIND = 4/**< 4*/};
    enum WORLDCHOCOBO {WCHOCO_WILD = 0/**< 0*/, WCHOCO_YELLOW = 2/**< 2*/, WCHOCO_GREEN = 3/**< 3*/, WCHOCO_BLUE = 4/**< 4*/, WCHOCO_BLACK = 5/**< 5*/, WCHOCO_GOLD = 6/**< 6*/};
    enum LOVER {LOVE_BARRET/**< 0*/, LOVE_TIFA/**< 1*/, LOVE_AERIS/**< 2*/, LOVE_YUFFIE/**< 3*/};
    enum MATERIACAVE {CAVE_MIME/**< 0*/, CAVE_HPMP/**< 1*/, CAVE_QUADMAGIC/**< 2*/, CAVE_KOTR/**< 3*/};
    enum SOUNDMODE {SOUND_MONO/**< 0*/, SOUND_STEREO/**< 1*/};
    enum CONTROLMODE {CONTROL_NORMAL/**< 0*/, CONTROL_CUSTOM/**< 1*/};
    enum CURSORMODE {CURSOR_INITIAL/**< 0*/, CURSOR_MEMORY/**< 1*/};
    enum ATBMODE {ATB_ACTIVE/**< 0*/, ATB_RECOMMENED, ATB_WAIT/**< 1*/};
    enum CAMERAMODE {CAMERA_AUTO/**< 0*/, CAMERA_FIXED/**< 1*/};
    enum MAGICORDER {MAGIC_RAI/**< 0*/, MAGIC_RIA/**< 1*/, MAGIC_AIR/**< 2*/, MAGIC_ARI/**< 3*/, MAGIC_IRA/**< 4*/, MAGIC_IAR/**< 5*/};
    /** \enum MENUITEMS
     *  \brief Menu items for ff7.
     */
    enum MENUITEMS {MENUITEM/**< 0*/, MENUMAGIC/**< 1*/, MENUMATERIA/**< 2*/, MENUEQUIPMENT/**< 3*/, MENUSTATUS/**< 4*/, MENUFORM/**< 5*/, MENULIMIT/**< 6*/, MENUCONFIG/**< 7*/, MENUPHS/**< 8*/, MENUSAVE/**< 9*/};
    /** \enum CONTROLACTION
     *  \brief Possible Actions the user can input
     */
    enum CONTROLACTION {
        ACTION_CAMERA/**< 0*/, ACTION_TARGET/**< 1*/, ACTION_PAGEUP/**< 2*/, ACTION_PAGEDOWN/**< 3*/,
        ACTION_MENU/**< 4*/, ACTION_OK/**< 5*/, ACTION_CANCEL/**< 6*/, ACTION_SWITCH/**< 7*/,
        ACTION_HELP/**< 8*/, ACTION_UNKNOWN1/**< 9*/, ACTION_UNKNOWN2/**< 10*/,
        ACTION_PAUSE/**< 11*/, ACTION_UP/**< 12*/, ACTION_RIGHT/**< 13*/, ACTION_DOWN/**< 14*/, ACTION_LEFT /**< 15*/
    };

    /** \enum PSXBUTTON
     *  \brief Final Fantasy 7 Buttons for when on PSX
     */
    enum PSXBUTTON {
        BTN_L2/**< 0*/, BTN_R2/**< 1*/, BTN_L1/**< 2*/, BTN_R1/**< 3*/,
        BTN_TRIANGLE/**< 4*/, BTN_CIRCLE/**< 5*/, BTN_X/**< 6*/, BTN_SQUARE/**< 7*/,
        BTN_SELECT/**< 8*/, BTN_UNKNOWN1/**< 9*/, BTN_UNKNOWN2/**< 10*/, BTN_START/**< 11*/,
        BTN_UP/**< 12*/, BTN_RIGHT/**< 13*/, BTN_DOWN/**< 14*/, BTN_LEFT /**< 15*/
    };
    /*! \enum KEYITEMS
     *  \brief ID's for each keyitem
     */
    enum KEYITEMS {
        COTTONDRESS/**< 0*/, SATINDRESS/**< 1*/, SILKDRESS/**< 2*/, WIG/**< 3*/, DYEDWIG/**< 4*/, BLONDEWIG/**< 5*/, GLASSTIARA/**< 6*/, RUBYTIATA/**< 7*/, DIAMONDTIARA/**< 8*/, COLOGNE/**< 9*/, FLOWERCOLOGNE/**< 10*/, SEXYCOLOGNE/**< 11*/, MEMBERSCARD/**< 12*/,
        LINGERIE/**< 13*/, MYSTERYPANTIES/**< 14*/, BIKINIBRIEFS/**< 15*/, PHARMACYCOUPON/**< 16*/, DISINFECTANT/**< 17*/, DEODORANT/**< 18*/, DIGESTIVE/**< 19*/, HUGEMATERIA_CONDOR/**< 20*/, HUGEMATERIA_COREL/**< 21*/, HUGEMATERIA_UNDERWATER/**< 22*/,
        HUGEMATERIA_ROCKET/**< 23*/, KEYTOANCIENTS/**< 24*/, LETTERTOADAUGHTER/**< 25*/, LETTERTOAWIFE/**< 26*/, LUNARHARP/**< 27*/, BASEMENTKEY/**< 28*/, KEYTOSECTOR5/**< 29*/, KEYCARD60/**< 30*/, KEYCARD62/**< 31*/, KEYCARD65/**< 32*/, KEYCARD66/**< 33*/,
        KEYCARD68/**< 34*/, MIDGARPARTS1/**< 35*/, MIDGARPARTS2/**< 36*/, MIDGARPARTS3/**< 37*/, MIDGARPARTS4/**< 38*/, MIDGARPARTS5/**< 39*/, PHS/**< 40*/, GOLDTICKET/**< 41*/, KEYSTONE/**< 42*/, LEIATHANSCALES/**< 43*/, GLACIERMAP/**< 44*/, COUPON_A/**< 45*/, COUPON_B/**< 46*/,
        COUPON_C/**< 47*/, BLACKMATERIA/**< 48*/, MYTHRIL/**< 49*/, SNOWBOARD /**< 50*/
    };
    //Functions
    explicit FF7Save(); /**< \brief create a new FF7Save object */
    //File Members

    /**
     * @brief fileFormat- Read a file and get its Format.
     * @param file - A File to check the format of
     * @return The Format of the file
     */
    inline FF7SaveInfo::FORMAT fileDataFormat(QFile &file) {
        return fileDataFormat(&file, file.fileName());
    }

    /**
     * @brief fileFormat- Read a file and get its Format.
     * @param io - A File to check the format of
     * @param fileName - A File Name to check the format of
     * @return The Format of the file
     */
    FF7SaveInfo::FORMAT fileDataFormat(QIODevice *io, const QString &fileName = QString());

    /**
     * @brief Say if file format is compressed
     * @param fileFormat - A File to check the format of
     * @return True is the format needs to be uncompressed
     */
    bool fileFormatIsCompressed(FF7SaveInfo::FORMAT fileFormat);

    /** \brief attempt to load fileName as ff7save
     *  \param fileName file that will be loaded
     *  \return True if Successful
    */
    bool loadFile(const QString &fileName);

    /** \brief attempt to uncompress the file if format is compressed
     *  \param io - Compressed file
     *  \return Uncompressed data or empty on error
    */
    QByteArray uncompressFile(QIODevice *io);

    /** \brief attempt to save fileName as ff7save
     *  \param fileName file that will be saved
     *  \param s the slot to be saved in case of single slot export.
     *  \return True if Successful
    */
    bool saveFile(const QString &fileName, int s = 0);

    /** \brief Export a File to the specificed format. Calls one of several internal methods to export the file.
    *  \param fileName file that will be saved
    *  \param exportFormat The Format to export.
    *  \param s Slot to export if exporting to a single slot save type
    *  \return True if Successful
    *  \sa exportPCFormat(),exportVMCFormat(),exportPSX(),exportPS3(),exportPGE(),exportPDA
    */
    bool exportFile(const QString &fileName, FF7SaveInfo::FORMAT exportFormat, int s = 0);

    /** \brief import from a file into a slot
     *
     *   Will import a slot from a file(fileName) into slot (s). when importing from a multi slot save type slot # (fileSlot) in the file will be imported.
     *  \param s slot to import into
     *  \param fileName file that will be imported
     *  \param fileSlot slot to import from fileName
     *  \return true if successful
    */
    bool importSlot(int s = 0, QString fileName = "", int fileSlot = 0);

    /** \brief clear a slot
     * \param s slot number (0-14)
     */
    void clearSlot(int s);

    /** \brief copy a slot Sin to the buffer
     * \param s slot number (0-14)
     */
    void copySlot(int s);

    /** \brief paste from the buffer into a slot
     * \param s slot number (0-14)
     */
    void pasteSlot(int s);

    /** \brief creates a new game in a slot
     * \param s slot number (0-14)
     * \param region: Region to make the save
     * \param fileName Raw PSX file to use instead of default data
     */
    void newGame(int s, const QString &region = QStringLiteral("NTSC-U"), const QString &fileName = QString()); //new game in slot s (over load default w/ fileName must be RAW PSX)

    /** \brief creates a new game + in a slot
     *
     * When creating a new game+ two char files will be exported. one for cait sith and another for vincent. those characters have to be reset to correctly set a new game. You can reimport the char files when you acquire the character in your new game +
     * \param s slot number (0-14)
     * \param CharFileName base filename to use for saving char files vincent and
     * \param fileName Raw PSX file to use instead of defalut data
     */
    void newGamePlus(int s, QString CharFileName, QString fileName = ""); //new game + in slot s (over load default w/ fileName must be RAW PSX

    /** \brief export a character
     * \param s slot number (0-14)
     * \param char_num character slot (0-8)
     * \param fileName file to write
     * \return true is successful
     */
    bool exportCharacter(int s, int char_num, QString fileName); // Write slot[s].char[char_num] to fileName

    /** \brief export a character
     * \param s slot number (0-14)
     * \param char_num character slot (0-8)
     * \param new_char raw bytes for a character in ff7
     */
    void importCharacter(int s, int char_num, QByteArray new_char); //import new_char to slot[s].char[char_num]

    /** \typedef QVector<QString> SubContainer
     * \brief used to hold more xml style string in metadata signing
     */
    typedef QVector< QString > SubContainer;

    /** \brief parse the metadata for 2012 / 2013 release
     *  \param fileName name of the file to output
     *  \param UserID squaresoft id number to when signing
     *  \return True is Successful
    */
    bool fixMetaData(QString fileName = "", QString UserID = "");

    /**
     * @brief generates a signature for PS3 or VMP based on input..
     * @param data: to generate signature for
     * @param keySeed: keySeed that will be used to sign the data
     * @return new Signature for the file
     */
    QByteArray generatePsSaveSignature(QByteArray data, QByteArray keySeed);

    QByteArray fileHeader(void);/**< \brief file Header as QByteArray*/

    /** \brief set the file header
     *  \param data: replace existing data with these bytes
     *  \return True is Successful
    */
    bool setFileHeader(QByteArray data);

    QByteArray slotHeader(int s); /**< \brief Header for a slot as QByteArray \param s slot number (0-14)*/

    /** \brief set the slot header
     *  \param s slot number (0-14)
     *  \param data: replace existing data with these bytes
     *  \return True is Successful
    */
    bool setSlotHeader(int s, QByteArray data);

    QByteArray slotFooter(int s);/**< \brief Footer for a slot as QByteArray \param s slot number (0-14)*/

    /** \brief set the slot footer
     *  \param s slot number (0-14)
     *  \param data: replace existing data with these bytes
     *  \return True is Successful
    */
    bool setSlotFooter(int s, QByteArray data);

    QByteArray slotPsxRawData(int s);/**< \brief QByteArray of a psx save (multiblock saves are ok)\param s slot number (0-14); if a multi block set s should be the first block used*/

    /** \brief set the slots raw psx data
     *
     *  Most Useful when connected to a hexEditor, This function will set the slot(s) raw data as if writing to a psx card directly. even if more then one slot and correctly update the save index based on whats in the data.
     *  \param s slot number (0-14)
     *  \param data: replace existing data with these bytes
     *  \return True is Successful
    */
    bool setSlotPsxRawData(int s, QByteArray data);

    QByteArray slotFF7Data(int s); /**< \brief Return Raw data from the slot \param s slot number (0-14)*/

    /** \brief
     *  \param s slot number (0-14)
     *  \param data: replace existing data with these bytes
     *  \overload setSlotFF7Data(int, const FF7SLOT&)
     */
    bool setSlotFF7Data(int s, QByteArray data);
    bool setSlotFF7Data(int s, const FF7SLOT &data);

    QList<QByteArray> slotIcon(int s); /**< \brief return slots save icon. each new frame will be appended to the list.*/

    /** \brief return the chocobos in the pen outside of the chocobo farm
     *  \param s slot number (0-14)
     *  \return list of chocobo in then pen.
    */
    QList<qint8> chocoboPens(int s);

    /** \brief return the chocobos in the pen outside of the chocobo farm
     *  \param s slot number (0-14)
     *  \param pen the slot in the pen to assign to (0-3)
     *  \param value rating of the chocobo (0:Empty 1:Wonderful 2:Great 3:Good 4:Fair 5:Average 6:Poor 7:Bad 8:Terrible)
    */
    void setChocoboPen(int s, int pen, qint8 value);

    /** \brief wins in fort condor mini game
     *  \param s slot number (0-14)
     *  \return number of wins at fort condor
    */
    quint8 condorWins(int s);

    /** \brief set how many time you have won the fort condor mini game
     *  \param s slot number (0-14)
     *  \param wins number of wins in the fort condor mini game
     */
    void setCondorWins(int s, quint8 wins);

    /** \brief losses in fort condor mini game
     *  \param s slot number (0-14)
     *  \return number of losses at fort condor
    */
    quint8 condorLosses(int s);

    /** \brief set how many time you have lost the fort condor mini game
     *  \param s slot number (0-14)
     *  \param losses number of losses in the fort condor mini game
    */
    void setCondorLosses(int s, quint8 losses);

    /** \return amount of gil you have donated to fort condor
     *  \param s slot number (0-14)
    */
    quint16 condorFunds(int s);

    /** \brief set how gil you have donated to  fort condor
     *  \param s slot number (0-14)
     *  \param value amount of gil donated
    */
    void setCondorFunds(int s, quint16 value);
    //Field Location

    /** \brief Id of the location save is located on
     *  \param s slot number (0-14)
     *  \return location id
     */
    quint16 locationId(int s);

    /** \brief set location id save is located on
     *  \param s slot number (0-14)
     *  \param locationID new locationID
     */
    void setLocationId(int s, quint16 locationID);

    /** \brief map id save is on
     * \param s slot number (0-14)
     * \return map id
    */
    quint16 mapId(int s);

    /** \brief set map id save is located on
     *  \param s slot number (0-14)
     *  \param mapID new mapID
     */
    void setMapId(int s, quint16 mapID);

    /** \brief x coordinate on field map
     * \param s slot number (0-14)
     * \return x coordinate
    */
    qint16 locationX(int s);

    /** \brief set x coordinate on field map
     * \param s slot number (0-14)
     * \param x new x coordinate
    */
    void setLocationX(int s, qint16 x);

    /** \brief y coordinate on field map
     * \param s slot number (0-14)
     * \return y coordinate
    */
    qint16 locationY(int s);

    /** \brief set y coordinate on field map
     * \param s slot number (0-14)
     * \param y new y coordinate
    */
    void setLocationY(int s, qint16 y);

    /** \brief triangle play is standing on. field map
     * \param s slot number (0-14)
     * \return triangle
    */
    quint16 locationT(int s);

    /** \brief set t coordinate on field map
     * \param s slot number (0-14)
     * \param t new t coordinate
    */
    void setLocationT(int s, quint16 t);

    /** \brief direction player is facing on field map
     * \param s slot number (0-14)
     * \return direction
    */
    quint8 locationD(int s);

    /** \brief set direction player is facing on field map
     * \param s slot number (0-14)
     * \param d new direction
    */
    void setLocationD(int s, quint8 d);

    /** \brief map the placeable save point is on
     *  \param s slot number (0-14)
     *  \return mapID of map containing the save point
     */
    quint16 craterSavePointMapID(int s);

    /** \brief x coordinate of the placeable save point
     *  \param s slot number (0-14)
     *  \return x coordinate of the placeable save point
    */
    qint16 craterSavePointX(int s);

    /** \brief y coordinate of the placeable save point
     *  \param s slot number (0-14)
     *  \return y coordinate of the placeable save point
    */
    qint16 craterSavePointY(int s);

    /** \brief z coordinate of the placeable save point
     *  \param s slot number (0-14)
     *  \return z coordinate of the placeable save point
    */
    qint16 craterSavePointZ(int s);

    /** \brief set the map that the placeable save point is on
     *  \param s slot number (0-14)
     *  \param value new mapID
     */
    void setCraterSavePointMapID(int s, int value);

    /** \brief set x coordinate of the placeable save point
     *  \param s slot number (0-14)
     *  \param value new x coordinate
    */
    void setCraterSavePointX(int s, int value);

    /** \brief set y coordinate of the placeable save point
     *  \param s slot number (0-14)
     *  \param value new y coordinate
    */
    void setCraterSavePointY(int s, int value);

    /** \brief set z coordinate of the placeable save point
     *  \param s slot number (0-14)
     *  \param value new z coordinate
    */
    void setCraterSavePointZ(int s, int value);

    //options
    /** \brief get controller mapping for a slot
     *
     *  The controller mapping while stored in the pc save is not used? and shouldn't be edited
     *  \param s slot number (0-14)
     *  \return Mapping as raw bytes
     */
    QByteArray controllerMapping(int s);

    /** \brief set the controller mapping for a slot
     *
     *  The controller mapping while stored in the pc save is not used? and shouldn't be edited
     *  \param s slot number (0-14)
     *  \param map Mapping as raw bytes
     */
    void setControllerMapping(int s, QByteArray map);

    /** \brief get button bound to an action for a slot
     *
     *  The controller mapping while stored in the pc save is not used? and shouldn't be edited
     *  \param s slot number (0-14)
     *  \param action game action ( FF7Save::CONTROLACTION )
     *  \return  FF7Save::PSXBUTTON that an action is mapped to
     */
    quint8 controllerMapping(int s, int action);

    /** \brief bind a button to an action for a slot.
     *
     *  The controller mapping while stored in the pc save is not used? and shouldn't be edited
     *  \param s slot number (0-14)
     *  \param action valid game action ( FF7Save::CONTROLACTION )
     *  \param button a valid button ( FF7Save::PSXBUTTON )
     */
    void setControllerMapping(int s, int action, int button);

    /** \brief In game options for a slot
     *  \param s slot number (0-14)
     *  \return game options in raw format
     */
    quint16 options(int s);

    /** \brief Set in game options for a slot
     *  \param s slot number (0-14)
     *  \param opt game options in raw format
     */
    void setOptions(int s, int opt);

    /** \brief soundMode mono or stero
     *  \param s slot number (0-14)
     *  return TRUE if Stero mode; FALSE for Mono
     */
    bool soundMode(int s);

    /** \brief setSound mode for a slot
     *  \param s slot number (0-14)
     *  \param mode: new soundMode FF7Save::SOUNDMODE
     */
    void setSoundMode(int s, int mode);

    void setSoundMode(int s, bool mode);
    bool controlMode(int s);
    void setControlMode(int s, int mode);
    void setControlMode(int s, bool mode);
    bool cursorMode(int s);
    void setCursorMode(int s, int mode);
    void setCursorMode(int s, bool mode);
    int atbMode(int s);
    void setAtbMode(int s, int mode);
    bool cameraMode(int s);
    void setCameraMode(int s, int mode);
    void setCameraMode(int s, bool mode);
    int magicOrder(int s);
    void setMagicOrder(int s, int order);
    bool battleHelp(int s);
    void setBattleHelp(int s, bool shown);
    int battleSpeed(int s);
    void setBattleSpeed(int s, int speed);
    int battleMessageSpeed(int s);
    void setBattleMessageSpeed(int s, int speed);
    int messageSpeed(int s);
    void setMessageSpeed(int s, int speed);
    bool fieldHelp(int s);
    void setFieldHelp(int s, bool shown);
    bool battleTargets(int s);
    void setBattleTargets(int s, bool shown);

    quint8 specialBattleWins(int s);
    void setSpecialBattleWins(int s, int wins);

    //Phs/Menu
    bool phsVisible(int s, int who);
    void setPhsVisible(int s, int who, bool checked);
    quint16 phsVisible(int s);
    void setPhsVisible(int s, quint16 phs_visible);
    bool phsAllowed(int s, int who);
    quint16 phsAllowed(int s);
    void setPhsAllowed(int s, int who, bool checked);
    void setPhsAllowed(int s, quint16 phs_visible);
    bool menuVisible(int s, int index);
    void setMenuVisible(int s, int index, bool checked);
    quint16 menuVisible(int s);
    void setMenuVisible(int s, quint16 menu_visible);
    bool menuLocked(int s, int index);
    void setMenuLocked(int s, int index, bool checked);
    quint16 menuLocked(int s);
    void setMenuLocked(int s, quint16 menu_visible);
    //item info
    quint16 item(int s, int item_num); //return raw ff7item
    QList<quint16> items(int s);// return all items
    void setItems(int s, QList<quint16> items);
    void setItem(int s, int item_num, quint16 rawitem);
    void setItem(int s, int item_num, quint16 new_id, quint8 new_qty);
    //materia get/set
    bool materiaCave(int s, MATERIACAVE cave);
    void setMateriaCave(int s, MATERIACAVE cave, bool isEmpty);
    quint8 partyMateriaId(int s, int mat_num);
    qint32 partyMateriaAp(int s, int mat_num);
    quint8 stolenMateriaId(int s, int mat_num);
    qint32 stolenMateriaAp(int s, int mat_num);
    void setPartyMateria(int s, int mat_num, quint8 id, qint32 ap);
    void setStolenMateria(int s, int mat_num, quint8 id, qint32 ap);
    //Description Stuff.
    quint32 descTime(int s);
    void setDescTime(int s, quint32 new_time);
    QString descName(int s);//return the name in the description
    void setDescName(int s, QString new_name); // desc name = new_name
    QString descLocation(int s);//return the location string used in the description
    void setDescLocation(int s, QString new_desc_location);//write new desc location string called from setLocation
    quint8 descLevel(int s);
    void setDescLevel(int s, int new_level);
    quint8 descParty(int s, int char_num);
    void setDescParty(int s, int char_num, quint8 new_id);
    quint16 descCurHP(int s);
    void setDescCurHP(int s, quint16 new_curHP);
    quint16 descMaxHP(int s);
    void setDescMaxHP(int s, quint16 new_maxHP);
    quint16 descCurMP(int s);
    void setDescCurMP(int s, quint16 new_curMP);
    quint16 descMaxMP(int s);
    void setDescMaxMP(int s, quint16 new_maxMP);
    quint32 descGil(int s);
    void setDescGil(int s, quint32 new_gil);
    //Dialog Colors
    QColor dialogColorUL(int s);
    QColor dialogColorUR(int s);
    QColor dialogColorLL(int s);
    QColor dialogColorLR(int s);
    void setDialogColorUL(int s, QColor color);
    void setDialogColorUR(int s, QColor color);
    void setDialogColorLL(int s, QColor color);
    void setDialogColorLR(int s, QColor color);
    // String Functions.
    QString chocoName(int s, int choco_num); //return choco_num's name.
    void setChocoName(int s, int choco_num, QString new_name); //write choco_num 's new_name to slot s
    QString location(int s);// return save location string
    void setLocation(int s, QString new_location);//set save location string to new_location
    quint32 gil(int s);
    void setGil(int s, quint32 gil);
    quint16 gp(int s);
    void setGp(int s, int gp);
    quint16 battles(int s);
    void setBattles(int s, int battles);
    quint16 runs(int s);
    void setRuns(int s, int runs);
    quint8 party(int s, int pos);
    /**
     * @brief Set the party member to an ID. When changing a party member the slots description data is also updated.
     * @param s - Slot to set th party in
     * @param pos - Party slot to set
     * @param new_id - Id of character
     */
    void setParty(int s, int pos, int new_id);
    qint8 chocoboPen(int s, int pos);
    void setChocoboPen(int s, int pos, int type);
    bool seenPandorasBox(int s);
    void setSeenPandorasBox(int s, bool seen);
    //Mini Game Stuff
    quint8 love(int s, bool battle, LOVER who);
    void setLove(int s, bool battle, LOVER who, quint8 love);
    quint16 speedScore(int s, int rank);
    void setSpeedScore(int s, int rank, quint16 score);
    quint16 bikeHighScore(int s);
    void setBikeHighScore(int s, quint16 score);
    QString snowboardTime(int s, int course);
    void setSnowboardTime(int s, int course, QString time);
    quint8 snowboardScore(int s, int course);
    void setSnowboardScore(int s, int course, quint8 score);
    quint32 countdownTimer(int s);
    void setCountdownTimer(int s, quint32 time);
    //Char Releated Functions
    FF7CHAR character(int s, int char_num); //Return Full Char
    quint8 charID(int s, int char_num); //Return Char ID
    quint8 charLevel(int s, int char_num); //Return Char Level
    quint8 charStr(int s, int char_num);
    quint8 charVit(int s, int char_num);
    quint8 charMag(int s, int char_num);
    quint8 charSpi(int s, int char_num);
    quint8 charDex(int s, int char_num);
    quint8 charLck(int s, int char_num);
    quint8 charStrBonus(int s, int char_num);
    quint8 charVitBonus(int s, int char_num);
    quint8 charMagBonus(int s, int char_num);
    quint8 charSpiBonus(int s, int char_num);
    quint8 charDexBonus(int s, int char_num);
    quint8 charLckBonus(int s, int char_num);
    qint8 charLimitLevel(int s, int char_num);
    quint8 charLimitBar(int s, int char_num);
    QString charName(int s, int char_num); //Return Char name
    quint8 charWeapon(int s, int char_num);
    quint8 charArmor(int s, int char_num);
    quint8 charAccessory(int s, int char_num);
    quint8 charFlag(int s, int char_num, int flag_num);
    quint16 charLimits(int s, int char_num); //Return Char ID
    quint16 charKills(int s, int char_num); //Return Char Level
    quint16 charTimesLimitUsed(int s, int char_num, int level);
    quint16 charCurrentHp(int s, int char_num);
    quint16 charBaseHp(int s, int char_num);
    quint16 charCurrentMp(int s, int char_num);
    quint16 charBaseMp(int s, int char_num);
    quint8 charUnknown(int s, int char_num, int unknown_num);
    quint16 charMaxHp(int s, int char_num);
    quint16 charMaxMp(int s, int char_num);
    quint32 charCurrentExp(int s, int char_num);
    quint32 charNextExp(int s, int char_num);
    quint8 charMateriaId(int s, int who, int mat_num);
    qint32 charMateriaAp(int s, int who, int mat_num);
    void setCharacter(int s, int char_num, const FF7CHAR &new_char);
    void setCharID(int s, int char_num, qint8 new_id);
    void setCharLevel(int s, int char_num, qint8 new_level);
    void setCharStr(int s, int char_num, quint8 str);
    void setCharVit(int s, int char_num, quint8 vit);
    void setCharMag(int s, int char_num, quint8 mag);
    void setCharSpi(int s, int char_num, quint8 spi);
    void setCharDex(int s, int char_num, quint8 dex);
    void setCharLck(int s, int char_num, quint8 lck);
    void setCharStrBonus(int s, int char_num, quint8 strbonus);
    void setCharVitBonus(int s, int char_num, quint8 vitbonus);
    void setCharMagBonus(int s, int char_num, quint8 magbonus);
    void setCharSpiBonus(int s, int char_num, quint8 spibonus);
    void setCharDexBonus(int s, int char_num, quint8 dexbonus);
    void setCharLckBonus(int s, int char_num, quint8 lckbonus);
    void setCharLimitLevel(int s, int char_num, qint8 limitlevel);
    void setCharLimitBar(int s, int char_num, quint8 limitbar);
    void setCharName(int s, int char_num, QString new_name); //write char_num 's new_name to slot s
    void setCharWeapon(int s, int char_num, quint8 weapon);
    void setCharArmor(int s, int char_num, quint8 armor);
    void setCharAccessory(int s, int char_num, quint8 accessory);
    void setCharFlag(int s, int char_num, int flag_num, quint8 flag_value);
    void setCharLimits(int s, int char_num, quint16 new_limits);
    void setCharKills(int s, int char_num, quint16 kills);
    void setCharTimeLimitUsed(int s, int char_num, int level, quint16 timesused);
    void setCharCurrentHp(int s, int char_num, quint16 curHp);
    void setCharBaseHp(int s, int char_num, quint16 baseHp);
    void setCharCurrentMp(int s, int char_num, quint16 curMp);
    void setCharBaseMp(int s, int char_num, quint16 baseMp);
    void setCharUnknown(int s, int char_num, int unknown_num, quint8 value);
    void setCharMaxHp(int s, int char_num, quint16 maxHp);
    void setCharMaxMp(int s, int char_num, quint16 maxMp);
    void setCharCurrentExp(int s, int char_num, quint32 exp);
    void setCharNextExp(int s, int char_num, quint32 next);
    void setCharMateria(int s, int who, int mat_num, quint8 id, qint32 ap);
    void setCharMateria(int s, int who, int mat_num, materia mat);
    //chocobo Stuff.
    QList<FF7CHOCOBO> chocobos(int s);
    QList<quint16> chocobosStaminas(int s);
    QList<QString> chocobosNames(int s);
    QList<bool> chocoboCantMates(int s);
    qint8 stablesOwned(int s);
    qint8 stablesOccupied(int s);
    qint8 stableMask(int s);
    void setStablesOwned(int s, qint8 value);
    void setStablesOccupied(int s, qint8 value);
    void setStableMask(int s, qint8 value);
    FF7CHOCOBO chocobo(int s, int chocoSlot);
    quint16 chocoStamina(int s, int chocoSlot);
    quint16 chocoSpeed(int s, int chocoSlot);
    quint16 chocoMaxSpeed(int s, int chocoSlot);
    quint16 chocoSprintSpeed(int s, int chocoSlot);
    quint16 chocoMaxSprintSpeed(int s, int chocoSlot);
    quint8 chocoSex(int s, int chocoSlot);
    quint8 chocoType(int s, int chocoSlot);
    quint8 chocoCoop(int s, int chocoSlot);
    quint8 chocoAccel(int s, int chocoSlot);
    quint8 chocoIntelligence(int s, int chocoSlot);
    quint8 chocoRaceswon(int s, int chocoSlot);
    quint8 chocoPCount(int s, int chocoSlot);
    quint8 chocoPersonality(int s, int chocoSlot);
    bool chocoCantMate(int s, int chocoSlot);
    void setChocoStamina(int s, int chocoSlot, quint16 stamina);
    void setChocoSpeed(int s, int chocoSlot, quint16 speed);
    void setChocoMaxSpeed(int s, int chocoSlot, quint16 maxspeed);
    void setChocoSprintSpeed(int s, int chocoSlot, quint16 sprintSpeed);
    void setChocoMaxSprintSpeed(int s, int chocoSlot, quint16 maxsprintSpeed);
    void setChocoSex(int s, int chocoSlot, quint8 value);
    void setChocoType(int s, int chocoSlot, quint8 value);
    void setChocoCoop(int s, int chocoSlot, quint8 value);
    void setChocoAccel(int s, int chocoSlot, quint8 value);
    void setChocoIntelligence(int s, int chocoSlot, quint8 value);
    void setChocoRaceswon(int s, int chocoSlot, quint8 value);
    void setChocoPCount(int s, int chocoSlot, quint8 value);
    void setChocoPersonality(int s, int chocoSlot, quint8 value);
    void setChocoCantMate(int s, int chocoSlot, bool cantMate);
    // Return File Info
    int lenFile(void);//Return File length.
    int lenFileHeader(void);//Return File Header length
    int lenCoreSave(void);//Return Slot length (data portion)
    int lenSlotHeader(void);//Return slot header length
    int lenSlotFooter(void);//Return slot footer length
    int lenSlot(void);//Return Slot length
    int numberOfSlots(void);//Return number of slots in the file_footer_dex
    QString fileName(void);//return loaded filename
    void setFileModified(bool, int s); //file changed toggle, with slot called
    void setRegion(int s, const QString &region);
    bool isFileModified(void);//has the file changed since load
    bool isSlotModified(int s);//has slot[s] changed since load.
    bool isSlotEmpty(int s);//is Slot s empty
    bool isFF7(int s);//valid ff7 slot?
    bool isPAL(int s);//PAL SLOT?
    bool isNTSC(int s);//NTSC SLOT??
    bool isJPN(int s);//is a Japanese File
    QString region(int s);// region string of slot s
    //Set Needed Info Stuffs

    char psx_block_type(int s);//mask of psx slot (used by index)
    void setPsx_block_type(int s, char block_type);
    quint8 psx_block_next(int s);// if using more then one block return location of next block
    void setPsx_block_next(int s, int next);
    quint8 psx_block_size(int s);//how many blocks save uses.
    void setPsx_block_size(int s, int blockSize);
    void fix_pc_bytemask(int s);// update so last slot is shown selected on load (must be public to set to currently viewed slot).
    //more data members
    QByteArray unknown(int s, int z);
    bool setUnknown(int s, int z, QByteArray data);
    quint16 steps(int s);
    void setSteps(int s, int steps);
    quint8 churchProgress(int s);
    void setChurchProgress(int s, int progress);
    quint8 donProgress(int s);
    void setDonProgress(int s, int progress);
    quint16 battlePoints(int s);
    void setBattlePoints(int s, quint16);
    quint32 time(int s);
    void setTime(int s, quint32 new_time);
    void setDisc(int s, int disc);
    quint8 disc(int s);
    quint16 mainProgress(int s);
    void setMainProgress(int s, int mProgress);
    QByteArray keyItems(int s);
    bool setKeyItems(int s, QByteArray data);
    bool keyItem(int s, int keyItem);
    void setKeyItem(int s, int keyItem, bool pickedUp);
    bool itemMask1(int s, int bit);
    void setItemMask1(int s, int bit, bool pickedUp);
    bool bmProgress1(int s, int bit);
    void setBmProgress1(int s, int bit, bool isTrue);
    void setBmProgress1(int s, int value);
    bool bmProgress2(int s, int bit);
    void setBmProgress2(int s, int bit, bool isTrue);
    void setBmProgress2(int s, int value);
    bool bmProgress3(int s, int bit);
    void setBmProgress3(int s, int bit, bool isTrue);
    void setBmProgress3(int s, int value);
    bool midgarTrainFlags(int s, int bit);
    void setMidgarTrainFlags(int s, int bit, bool isTrue);
    void setMidgarTrainFlags(int s, int value);
    bool turtleParadiseFlyerSeen(int s, int flyer);
    quint8 turtleParadiseFlyersSeen(int s);
    void setTurtleParadiseFlyerSeen(int s, int flyer, bool seen);
    void setTurtleParadiseFlyersSeen(int s, quint8 flyersSeen);
    bool startBombingMission(int s);
    void setStartBombingMission(int s, bool isTrue);
    quint32 uWeaponHp(int s);
    void setUWeaponHp(int s, int hp);
    bool killedEmeraldWeapon(int s);
    void setKilledEmeraldWeapon(int s, bool isTrue);
    bool killedRubyWeapon(int s);
    void setKilledRubyWeapon(int s, bool isTrue);
    quint8 tutSave(int s);
    void setTutSave(int s, int value);
    bool canFightNinjaInForest(int s);
    void setCanFightNinjaInForest(int s, bool isTrue);
    quint8 tutSub(int s);
    bool tutSub(int s, int bit);
    void setTutSub(int s, int bit, bool isTrue);
    void setTutSub(int s, int value);

    /** \brief has yuffie been unlocked
     * \param s slot number (0-14)
     *  \return True if yuffie has been unlocked
    */
    bool yuffieUnlocked(int s);

    /** \brief set if yuffie has been unlocked
     * \param s slot number (0-14)
     * \param isUnlocked Is Character Unlocked?
     */
    void setYuffieUnlocked(int s, bool isUnlocked);

    /** \brief has vincent been unlocked
     * \param s slot number (0-14)
     *  \return True if vincent has been unlocked
    */
    bool vincentUnlocked(int s);

    /** \brief set if vincent has been unlocked
    * \param s slot number (0-14)
    * \param isUnlocked Is Character Unlocked?
    */
    void setVincentUnlocked(int s, bool isUnlocked);

    bool worldChocobo(int s, int bit);
    void setWorldChocobo(int s, int bit, bool isTrue);
    bool worldVehicle(int s, int bit);
    void setWorldVehicle(int s, int bit, bool isTrue);
    //World Coords
    quint32 worldCoordsLeader(int s, bool firstChunk);
    int worldCoordsLeaderX(int s);
    int worldCoordsLeaderID(int s);
    int worldCoordsLeaderAngle(int s);
    int worldCoordsLeaderY(int s);
    int worldCoordsLeaderZ(int s);
    void setWorldCoordsLeader(int s, bool firstChunk, int value);
    void setWorldCoordsLeaderX(int s, int value);
    void setWorldCoordsLeaderID(int s, int value);
    void setWorldCoordsLeaderAngle(int s, int value);
    void setWorldCoordsLeaderY(int s, int value);
    void setWorldCoordsLeaderZ(int s, int value);
    quint32 worldCoordsTc(int s, bool firstChunk);
    int worldCoordsTcX(int s);
    int worldCoordsTcID(int s);
    int worldCoordsTcAngle(int s);
    int worldCoordsTcY(int s);
    int worldCoordsTcZ(int s);
    void setWorldCoordsTc(int s, bool firstChunk, int value);
    void setWorldCoordsTcX(int s, int value);
    void setWorldCoordsTcID(int s, int value);
    void setWorldCoordsTcAngle(int s, int value);
    void setWorldCoordsTcY(int s, int value);
    void setWorldCoordsTcZ(int s, int value);
    quint32 worldCoordsBh(int s, bool firstChunk);
    int worldCoordsBhX(int s);
    int worldCoordsBhID(int s);
    int worldCoordsBhAngle(int s);
    int worldCoordsBhY(int s);
    int worldCoordsBhZ(int s);
    void setWorldCoordsBh(int s, bool firstChunk, int value);
    void setWorldCoordsBhX(int s, int value);
    void setWorldCoordsBhID(int s, int value);
    void setWorldCoordsBhAngle(int s, int value);
    void setWorldCoordsBhY(int s, int value);
    void setWorldCoordsBhZ(int s, int value);
    quint32 worldCoordsSub(int s, bool firstChunk);
    int worldCoordsSubX(int s);
    int worldCoordsSubID(int s);
    int worldCoordsSubAngle(int s);
    int worldCoordsSubY(int s);
    int worldCoordsSubZ(int s);
    void setWorldCoordsSub(int s, bool firstChunk, int value);
    void setWorldCoordsSubX(int s, int value);
    void setWorldCoordsSubID(int s, int value);
    void setWorldCoordsSubAngle(int s, int value);
    void setWorldCoordsSubY(int s, int value);
    void setWorldCoordsSubZ(int s, int value);
    quint32 worldCoordsWchoco(int s, bool firstChunk);
    int worldCoordsWchocoX(int s);
    int worldCoordsWchocoID(int s);
    int worldCoordsWchocoAngle(int s);
    int worldCoordsWchocoY(int s);
    int worldCoordsWchocoZ(int s);
    void setWorldCoordsWchoco(int s, bool firstChunk, int value);
    void setWorldCoordsWchocoX(int s, int value);
    void setWorldCoordsWchocoID(int s, int value);
    void setWorldCoordsWchocoAngle(int s, int value);
    void setWorldCoordsWchocoY(int s, int value);
    void setWorldCoordsWchocoZ(int s, int value);
    quint32 worldCoordsDurw(int s, bool firstChunk);
    int worldCoordsDurwX(int s);
    int worldCoordsDurwID(int s);
    int worldCoordsDurwAngle(int s);
    int worldCoordsDurwY(int s);
    int worldCoordsDurwZ(int s);
    void setWorldCoordsDurw(int s, bool firstChunk, int value);
    void setWorldCoordsDurwX(int s, int value);
    void setWorldCoordsDurwID(int s, int value);
    void setWorldCoordsDurwAngle(int s, int value);
    void setWorldCoordsDurwY(int s, int value);
    void setWorldCoordsDurwZ(int s, int value);
    void setSaveNumber(int s, int saveNum);

    bool subMiniGameVictory(int s);
    void setSubMiniGameVictory(int s, bool won);

    /** \brief Did Cloud play piano durring the flashback?.
     *
     * \return True if the player played the piano durring the flashback
     * \param s slot number (0-14)
     */
    bool playedPianoOnFlashback(int s);

    /** \brief Set if Cloud played piano durring the flashback.
     *
     * \param s slot number (0-14)
     * \param played True = Cloud Played piano
     */
    void setPlayedPianoOnFlashback(int s, bool played);

    /** \brief Get Choco Billy's Rating of a chocobo.
     *
     * This is the rating that Choco Billy give to a chocobo it follows the same format as FF7Save::chocoboPen()
     * \param s slot number (0-14)
     * \param stable stable number (0-5)
     */
    quint8 chocoboRating(int s, int stable);

    /** \brief Set Choco Billy's Rating of a chocobo.
     *
     * This is the rating that Choco Billy give to a chocobo it follows the same format as FF7Save::chocoboPen()
     * \param s slot number (0-14)
     * \param stable stable number 0-5
     * \param rating (0-8) 0:empty 1: wonderful 8:terrible
     */
    void setChocoboRating(int s, int stable, int rating);
    QList<quint8> chocoboRatings(int s);

    /** \brief Get Description Text for PSX Slot.
     *
     * This text is the text shown when you view the save slot in the memory manager on the playstation. It is also visible in many programs that work with psx memory cards.
     * \param s slot number (0-14)
     */
    QString psxDesc(int s);

    /** \brief Set The Description Text for PSX Slot (text shows in memory card manager of playstation) USE WITH CAUTION CAN RETURN JUNK DATA
     *
     * This text is the text shown when you view the save slot in the memory manager on the playstation. It is also visible in many programs that work with psx memory cards.
     *
     * \param newDesc your new text
     * \param s slot number (0-14)
     */
    void setPsxDesc(QString newDesc, int s);

    /**
     * @brief the number of unknown z vars.
     * @return Number Of "z" vars in ff7save
     */
    inline int unknown_zmax()
    {
        return 48; //Number of "z" vars.
    }

    /**
     * @brief Set the format of the loaded file
     * @param newFormat a valid FF7SaveInfo::FORMAT
     */
    void setFormat(FF7SaveInfo::FORMAT newFormat);

    /**
     * @brief Returns the format of the loaded file
     * @return FF7SaveInfo::FORMAT
     */
    FF7SaveInfo::FORMAT format();

    bool isBufferSlotPopulated();/**< \brief True when the bufferslot is populated */
signals:
    void fileChanged(bool);/**< \brief emits when internal data changes */

private:
    /** \brief attempt to save fileName as a PC Format save
     *  \param fileName file that will be saved
     *  \param exportFormat PC type to export FF7SaveInfo::FORMAT::PC or FF7SaveInfo::FORMAT::SWITCH
     *  \return True if Successful
    */
    bool exportPCFormat(const QString &fileName, FF7SaveInfo::FORMAT exportFormat);

    /** \brief attempt to save fileName as a VMC Format save
     *  \param fileName file that will be saved
     *  \param exportFormat VMC type to export FF7SaveInfo::FORMAT::VMC, FF7SaveInfo::FORMAT::VGS or FF7SaveInfo::FORMAT::DEX
     *  \return True if Successful
    */
    bool exportVMCFormat(const QString &fileName, FF7SaveInfo::FORMAT exportFormat);

    /** \brief attempt to a Slot as as Single Slot format
     *  \param fileName file that will be saved
     *  \param exportFormat VMC type to export FF7SaveInfo::FORMAT::PSX, FF7SaveInfo::FORMAT::PGE, FF7SaveInfo::FORMAT::PDA or FF7SaveInfo::FORMAT::PS3
     *  \param s Slot to export.
     *  \return True if Successful
    */
    bool exportSlot(const QString &fileName, FF7SaveInfo::FORMAT exportFormat, int s);

    /**
     * @brief md5sum Generate an md5sum for a save file used for metadata generation
     * @param fileName file to sum
     * @param UserID the users ID,
     * @return A QString that contains the md5sum or an empty string if its failed
     */
    QString md5sum(QString fileName, QString UserID);

    QString fileblock(const QString &fileName);
    QString filetimestamp(QString fileName);
    void checksumSlots();
    [[ deprecated ("FF7Save::ff7Checksum Removed, Use FF7SLOT.updateChecksum() and / or FF7SLOT.isEmpty()") ]]quint16 ff7Checksum(int s);
    void fix_psv_header(int s, int blocks = 1);
    void fix_pge_header(int s);
    void fix_pda_header(int s);
    void fix_psx_header(int s);
    void fix_vmp_header(void);
    void fix_vmc_header(void);
    void vmcRegionEval(int s);
    //data members
    FF7SLOT buffer_slot;// hold a buffer slot
    FF7SLOT slot[15]; //core slot data.
    FF7HEADFOOT hf[15]; //slot header and footer.
    FF7SaveInfo::FORMAT fileFormat = FF7SaveInfo::FORMAT::UNKNOWN;
    QByteArray _bufferFileHeader;
    QByteArray _fileHeader;
    bool slotChanged[15];
    bool fileHasChanged;
    QString buffer_region; // hold the buffers region data.
    QList<QString> SG_Region_String;
    QString filename;//opened file
    QVector< SubContainer > parseXML(const QString &fileName, const QString &metadataPath, const QString &UserID);
    QVector< SubContainer > createMetadata(const QString &fileName, const QString &UserID);

    inline static const auto allDigetRegEx = QRegularExpression(QStringLiteral("^\\d+$"));
    inline static const QString invalidRegion = QStringLiteral("\u0000\u0000\u0000\u0000\u0000\u0000\u0000\u0000\u0000\u0000\u0000\u0000\u0000\u0000\u0000\u0000\u0000\u0000\u0000\u0000");
};
