#include "lhgl_camera.h"

namespace lh_gl {

    const static float STEP_SCALE = 1.0f;
    const static float EDGE_STEP = 0.5f;
    const static int MARGIN = 10;

    Camera::Camera(int WindowWidth, int WindowHeight)
    {
        m_windowWidth = WindowWidth;
        m_windowHeight = WindowHeight;
        m_pos = Vector3f(0.0f, 0.0f, 0.0f);
        m_target = Vector3f(0.0f, 0.0f, 1.0f);
        m_target.Normalize();
        m_up = Vector3f(0.0f, 1.0f, 0.0f);

        Init();
    }


    Camera::Camera(int WindowWidth, int WindowHeight, const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up)
    {
        m_windowWidth = WindowWidth;
        m_windowHeight = WindowHeight;
        m_pos = Pos;

        m_target = Target;
        m_target.Normalize();

        m_up = Up;
        m_up.Normalize();

        Init();
    }


    void Camera::Init()
    {
        Vector3f HTarget(m_target.x, 0.0, m_target.z);
        HTarget.Normalize();

        if (HTarget.z >= 0.0f)
        {
            if (HTarget.x >= 0.0f)
            {
                m_AngleH = 360.0f - ToDegree(asin(HTarget.z));
            }
            else
            {
                m_AngleH = 180.0f + ToDegree(asin(HTarget.z));
            }
        }
        else
        {
            if (HTarget.x >= 0.0f)
            {
                m_AngleH = ToDegree(asin(-HTarget.z));
            }
            else
            {
                m_AngleH = 180.0f - ToDegree(asin(-HTarget.z));
            }
        }

        m_AngleV = -ToDegree(asin(m_target.y));

        m_OnUpperEdge = false;
        m_OnLowerEdge = false;
        m_OnLeftEdge = false;
        m_OnRightEdge = false;
        m_mousePos.x = m_windowWidth / 2;
        m_mousePos.y = m_windowHeight / 2;

        // glutWarpPointer(m_mousePos.x, m_mousePos.y);
    }


    bool Camera::on_keyboard(LHGL_KEY Key)
    {
        bool Ret = false;
        switch (Key) 
        {
        case LHGL_KEY_UP:
        case LHGL_KEY_W:
        case LHGL_KEY_w:
        {
            m_pos += (m_target * STEP_SCALE);
            Ret = true;
        }
        break;
        case LHGL_KEY_DOWN:
        case LHGL_KEY_S:
        case LHGL_KEY_s:
        {
            m_pos -= (m_target * STEP_SCALE);
            Ret = true;
        }
        break;
        case LHGL_KEY_LEFT:
        case LHGL_KEY_A:
        case LHGL_KEY_a:
        {
            Vector3f Left = m_target.Cross(m_up);
            Left.Normalize();
            Left *= STEP_SCALE;
            m_pos += Left;
            Ret = true;
        }
        break;
        case LHGL_KEY_RIGHT:
        case LHGL_KEY_D:
        case LHGL_KEY_d:
        {
            Vector3f Right = m_up.Cross(m_target);
            Right.Normalize();
            Right *= STEP_SCALE;
            m_pos += Right;
            Ret = true;
        }
        break;
        case LHGL_KEY_PAGE_UP:
            m_pos.y += STEP_SCALE;
            break;

        case LHGL_KEY_PAGE_DOWN:
            m_pos.y -= STEP_SCALE;
            break;

        default:
            break;
        }
        return Ret;
    }


    bool Camera::om_mouse(int x, int y)
    {
        const int DeltaX = m_mousePos.x - x;
        const int DeltaY = m_mousePos.y - y;

        m_mousePos.x = x;
        m_mousePos.y = y;

        m_AngleH += (float)DeltaX / 20.0f;
        m_AngleV += (float)DeltaY / 20.0f;

        if (DeltaX == 0) {
            if (x <= MARGIN) {
                //    m_AngleH -= 1.0f;
                m_OnLeftEdge = true;
            }
            else if (x >= (m_windowWidth - MARGIN)) {
                //    m_AngleH += 1.0f;
                m_OnRightEdge = true;
            }
        }
        else {
            m_OnLeftEdge = false;
            m_OnRightEdge = false;
        }

        if (DeltaY == 0) {
            if (y <= MARGIN) {
                m_OnUpperEdge = true;
            }
            else if (y >= (m_windowHeight - MARGIN)) {
                m_OnLowerEdge = true;
            }
        }
        else {
            m_OnUpperEdge = false;
            m_OnLowerEdge = false;
        }

        Update();
        return true;
    }


    void Camera::OnRender()
    {
        bool ShouldUpdate = false;

        if (m_OnLeftEdge) {
            m_AngleH -= EDGE_STEP;
            ShouldUpdate = true;
        }
        else if (m_OnRightEdge) {
            m_AngleH += EDGE_STEP;
            ShouldUpdate = true;
        }

        if (m_OnUpperEdge) {
            if (m_AngleV > -90.0f) {
                m_AngleV -= EDGE_STEP;
                ShouldUpdate = true;
            }
        }
        else if (m_OnLowerEdge) {
            if (m_AngleV < 90.0f) {
                m_AngleV += EDGE_STEP;
                ShouldUpdate = true;
            }
        }

        if (ShouldUpdate) {
            Update();
        }
    }

    void Camera::Update()
    {
//       y^   ^z
//        |  /
//        | /
//  -----0/---->x
//       /|
//      / | 
//默认相机朝向z轴正方向,右边是x轴正方向,up就是y轴正方向。
        const Vector3f vaxis(0.0f, 1.0f, 0.0f);//默认vaxis就是相机朝向方向。

        Vector3f view(1.0f, 0.0f, 0.0f);
        view.Rotate(m_AngleH, vaxis);//向量view绕vaxis(y轴)旋转m_AngleH度。
        view.Normalize();

        Vector3f haxis = vaxis.Cross(view);//获得垂直于vaxis与view平面的向量haxis
        haxis.Normalize();
        view.Rotate(m_AngleV, haxis);//向量View绕Haxis旋转m_AngleV度。
  
        m_target = view;//新的相机方向。
        m_target.Normalize();

        m_up = m_target.Cross(haxis);//修复相机up
        m_up.Normalize();
    }


    void Camera::AddToATB(TwBar* bar)
    {
        TwAddButton(bar, "Camera", NULL, NULL, "");
        TwAddVarRW(bar, "Position", TW_TYPE_LHGL_VECTOR3F, (void*)&m_pos, NULL);
        TwAddVarRO(bar, "Direction", TW_TYPE_DIR3F, &m_target, " axisz=-z ");
    }
}