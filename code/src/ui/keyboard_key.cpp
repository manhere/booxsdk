#include "onyx/sys/sys.h"
#include "onyx/ui/keyboard_utils.h"
#include "onyx/ui/keyboard_key.h"
#include "onyx/ui/keyboard_layout.h"
#include "onyx/ui/keyboard_direction_dialog.h"
#include "onyx/screen/screen_proxy.h"

namespace ui
{

const QString STANDARD_KEY_BUTTON_STYLE = "      \
QPushButton                             \
{                                       \
    background: white;                  \
    font-size: 24px;                    \
    border-width: 1px;                  \
    border-color: black;                \
    border-style: solid;                \
    color: black;                       \
    padding: 0px;                       \
}                                       \
QPushButton:pressed                     \
{                                       \
    padding-left: 0px;                  \
    padding-top: 0px;                   \
    color: white;                       \
    border-color: white;                \
    background-color: black;            \
}                                       \
QPushButton:focus                       \
{                                       \
    border-width: 3px;                  \
    border-color: black;                \
    border-style: solid;                \
}                                       \
QPushButton:checked                     \
{                                       \
    padding-left: 0px;                  \
    padding-top: 0px;                   \
    color: white;                       \
    border-color: white;                \
    background-color: black;            \
}                                       \
QPushButton:disabled                    \
{                                       \
    color:transparent;                  \
    border-color:transparent;           \
    background-color:transparent;       \
}";

const QString CENTER_KEY_BUTTON_STYLE = "      \
QPushButton                             \
{                                       \
    background: white;                  \
    font-size: 24px;                    \
    border-width: 1px;                  \
    border-color: black;                \
    border-style: solid;                \
    color: black;                       \
    padding: 0px;                       \
}                                       \
QPushButton:pressed                     \
{                                       \
    padding-left: 0px;                  \
    padding-top: 0px;                   \
    color: white;                       \
    border-color: white;                \
    background-color: black;            \
}                                       \
QPushButton:focus                       \
{                                       \
    border-width: 3px;                  \
    border-color: black;                \
    border-style: solid;                \
}                                       \
QPushButton:checked                     \
{                                       \
    padding-left: 0px;                  \
    padding-top: 0px;                   \
    color: white;                       \
    border-color: white;                \
    background-color: black;            \
}                                       \
QPushButton:disabled                    \
{                                       \
    color:transparent;                  \
    border-color:transparent;           \
    background-color:transparent;       \
}";

const QString FUNCTION_KEY_BUTTON_STYLE = "      \
QPushButton                             \
{                                       \
    background: white;                  \
    font-size: 12px;                    \
    border-width: 1px;                  \
    border-color: black;                \
    border-style: solid;                \
    color: black;                       \
    padding: 0px;                       \
}                                       \
QPushButton:pressed                     \
{                                       \
    padding-left: 0px;                  \
    padding-top: 0px;                   \
    color: white;                       \
    border-color: white;                \
    background-color: black;            \
}                                       \
QPushButton:focus                       \
{                                       \
    border-width: 3px;                  \
    border-color: black;                \
    border-style: solid;                \
}                                       \
QPushButton:checked                     \
{                                       \
    padding-left: 0px;                  \
    padding-top: 0px;                   \
    color: white;                       \
    border-color: white;                \
    background-color: black;            \
}                                       \
QPushButton:disabled                    \
{                                       \
    color:transparent;                  \
    border-color:transparent;           \
    background-color:transparent;       \
}";

//static QSize getKeySize(int code)
//{
//    QChar ch(code);
//    int standard_key_size = standardKeySize();
//
//    if (ch.isNumber())
//    {
//        if (isSwedish())
//        {
//            return QSize(47,47);
//        }
//
//        if (isPolish() || isHungarian())
//        {
//            return QSize(standard_key_size, standard_key_size);
//        }
//        return QSize(52, 52);
//    }
//
//    if (code < BSCode)
//    {
//        return QSize(standard_key_size, standard_key_size);
//    }
//
//    if (code > UnknownCode)
//    {
//        return QSize(standard_key_size, standard_key_size);
//    }
//
//    if (code == Blank)
//    {
//        bool has_touch = SysStatus::instance().hasTouchScreen();
//        int len = (standard_key_size * (has_touch ? 4 : 6)) + (has_touch ? 12 : 20);
//        if ((isRussian() && isEnglishLayout()) || isPolish() || isHungarian())
//        {
//            len = standard_key_size * (has_touch ? 2 : 4) + (has_touch ? 4 : 12);
//        }
//        return QSize(len, standard_key_size);
//    }
//
//    if (code == EnterCode)
//    {
//        return QSize(((standard_key_size << 1) + 4) , standard_key_size);
//    }
//
//    if (code == BackSpace)
//    {
//        return QSize(((standard_key_size << 1) + 4), standard_key_size);
//    }
//
//    if (code == BackSlash)
//    {
//        return QSize(standard_key_size, standard_key_size);
//    }
//
//    if (code == DeleteCode)
//    {
//        return QSize(standard_key_size, standard_key_size);
//    }
//
//    if (code == ShiftCode)
//    {
//        return QSize(((standard_key_size << 1) + 4), standard_key_size);
//    }
//
//    if (code == HandWriting)
//    {
//        return QSize(((standard_key_size << 1) + 4), standard_key_size);
//    }
//
//    if (code == SwitchLanguage)
//    {
//        return QSize(((standard_key_size << 1) + 4), standard_key_size);
//    }
//
//    if (code == CapLock)
//    {
//       return QSize(((standard_key_size << 1) + 4), standard_key_size);
//    }
//
//    return QSize(standard_key_size, standard_key_size);
//}

static QPoint getArrowDisplayPosition(const QRect & key_rect, const QSize & image_size, KeyboardDirection direction)
{
    QPoint pos = key_rect.topLeft();
    switch (direction)
    {
    case KEYBOARD_UP:
        pos.setX(key_rect.left() + ((key_rect.width() - image_size.width()) >> 1));
        pos.setY(key_rect.top());
        break;
    case KEYBOARD_DOWN:
        pos.setX(key_rect.left() + ((key_rect.width() - image_size.width()) >> 1));
        pos.setY(key_rect.height() - image_size.height());
        break;
    case KEYBOARD_LEFT:
        pos.setX(key_rect.left());
        pos.setY(key_rect.top() + ((key_rect.height() - image_size.height()) >> 1));
        break;
    case KEYBOARD_RIGHT:
        pos.setX(key_rect.right() - image_size.width());
        pos.setY(key_rect.top() + ((key_rect.height() - image_size.height()) >> 1));
        break;
    default:
        break;
    }
    return pos;
}

KeyBoardKey::KeyBoardKey(KeyboardLayout *layout, QWidget *parent)
    : QPushButton(parent)
    , locked_(false)
    , shifted_(false)
    , display_arrow_(false)
    , code_(BSCode)
    , shift_code_(BSCode)
    , direction_(KEYBOARD_NORMAL)
    , layout_(layout)
{
}

KeyBoardKey::~KeyBoardKey()
{
}

void KeyBoardKey::setCode(const int code, const int location, const KeyboardDirection direction)
{
    code_ = code;
    shift_code_ = code;
    direction_ = direction;

    if (code == ShiftCode ||
        code == CapLock ||
        code == SwitchLanguage ||
        code == HandWriting ||
        code == EnterCode ||
        code == Blank)
    {
        setStyleSheet(FUNCTION_KEY_BUTTON_STYLE);
    }
    else if (location == KEYBOARD_CENTER)
    {
        setStyleSheet(CENTER_KEY_BUTTON_STYLE);
    }
    else
    {
        setStyleSheet(STANDARD_KEY_BUTTON_STYLE);
    }

    // TODO. set the size of the button
    if (code > BSCode && code < UnknownCode)
    {
        // set the size and image of the special key
        SpecialMaps & special_maps = layout_->specialMaps();
        setText(special_maps[code - BSCode - 1].label);

        if (code == ShiftCode || code == CapLock)
        {
            setCheckable(true);
        }
    }
    else
    {
        // set the size and text of the regular key
        QChar text(code);
        setText(QString(text));
    }

    if (code == BackSpace)
    {
        QPixmap back_map(":/images/back_spac.png");
        setIcon(QIcon(back_map));
        setIconSize(back_map.size());
    }

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setFixedSize(layout_->getKeySize(code));
}

bool KeyBoardKey::isShiftKey()
{
    QChar c(code_);
    if (layout_->shiftMap().contains(c))
    {
        return true;
    }
    return false;
}

void KeyBoardKey::onShifted(bool shifted)
{
    shifted_ = shifted;
    updateText();
}

void KeyBoardKey::onCapLocked(bool cap_locked)
{
    locked_ = cap_locked;
    updateText();
}

void KeyBoardKey::updateText()
{
    QChar c(code_);
    if (shifted_ && isShiftKey())
    {
        ShiftMap & shift_map = layout_->shiftMap();
        shift_code_ = shift_map[code_].unicode();
    }
    else if (c.isLetter() && locked_)
    {
        shift_code_ = c.toUpper().unicode();
    }
    else
    {
        shift_code_ = code_;
    }

    if (isShiftKey() || c.isLetter())
    {
        setText(QChar(shift_code_));
    }
    
    if (code_ == QChar('7') && shifted_)
    {
        setText("&&");
    }
}

void KeyBoardKey::keyPressEvent(QKeyEvent * event)
{
    event->accept();
}

void KeyBoardKey::keyReleaseEvent(QKeyEvent * event)
{
    int key = event->key();
    switch (key)
    {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        if (direction_ == KEYBOARD_CENTER && display_arrow_)
        {
            emit directionKeyPressed(KEYBOARD_CENTER);
            event->accept();
        }
        else
        {
            event->accept();
            click();
        }
        break;
    case Qt::Key_Up:
        if (direction_ == KEYBOARD_CENTER && display_arrow_)
        {
            emit directionKeyPressed(KEYBOARD_UP);
            event->accept();
            return;
        }
        break;
    case Qt::Key_Down:
        if (direction_ == KEYBOARD_CENTER && display_arrow_)
        {
            emit directionKeyPressed(KEYBOARD_DOWN);
            event->accept();
            return;
        }
        break;
    case Qt::Key_Left:
        if (direction_ == KEYBOARD_CENTER && display_arrow_)
        {
            emit directionKeyPressed(KEYBOARD_LEFT);
            event->accept();
            return;
        }
        break;
    case Qt::Key_Right:
        if (direction_ == KEYBOARD_CENTER && display_arrow_)
        {
            emit directionKeyPressed(KEYBOARD_RIGHT);
            event->accept();
            return;
        }
        break;
    default:
        break;
    }
    event->ignore();
}

void KeyBoardKey::mousePressEvent(QMouseEvent *me)
{
    onyx::screen::instance().enableUpdate(false);
    QPushButton::mousePressEvent(me);
    onyx::screen::instance().enableUpdate(true);
    onyx::screen::instance().updateWidget(this, onyx::screen::ScreenProxy::DW);
}

void KeyBoardKey::onDisplayArrow(bool display)
{
    if (display_arrow_ != display)
    {
        display_arrow_ = display;
        update();
    }
}

void KeyBoardKey::paintEvent(QPaintEvent *pe)
{
    QPushButton::paintEvent(pe);
    if (display_arrow_)
    {
        static QImage up_image(":/images/keyboard_up.png");
        static QImage down_image(":/images/keyboard_down.png");
        static QImage left_image(":/images/keyboard_left.png");
        static QImage right_image(":/images/keyboard_right.png");
        if (direction_ == KEYBOARD_UP || direction_ == KEYBOARD_DOWN || direction_ == KEYBOARD_LEFT || direction_ == KEYBOARD_RIGHT)
        {
            QPainter painter(this);
            QImage image;
            switch (direction_)
            {
            case KEYBOARD_UP:
                image = up_image;
                break;
            case KEYBOARD_DOWN:
                image = down_image;
                break;
            case KEYBOARD_LEFT:
                image = left_image;
                break;
            case KEYBOARD_RIGHT:
                image = right_image;
                break;
            default:
                break;
            }
            if (!image.isNull())
            {
                QPoint pt = getArrowDisplayPosition(rect(), image.size(), direction_);
                painter.drawImage(pt, image);
            }
        }
    }
}

void KeyBoardKey::resizeEvent(QResizeEvent *re)
{
    QPushButton::resizeEvent(re);
}

void KeyBoardKey::mouseReleaseEvent(QMouseEvent* me)
{
    onyx::screen::instance().enableUpdate(false);
    QPushButton::mouseReleaseEvent(me);
    onyx::screen::instance().enableUpdate(true);

    // screen::ScreenManager::instance().fastUpdateWidget(this, true, false);
}

bool KeyBoardKey::event(QEvent * e)
{
    switch (e->type())
    {
    case QEvent::MouseMove:
    case QEvent::HoverMove:
    case QEvent::HoverEnter:
    case QEvent::HoverLeave:
        e->accept();
        return true;
    default:
        break;
    }
    return QPushButton::event(e);
}

}   // namespace ui
