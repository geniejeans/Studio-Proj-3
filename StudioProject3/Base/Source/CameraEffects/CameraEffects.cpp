#include "CameraEffects.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "../EntityManager.h"
#include "GL\glew.h"

CCameraEffects::CCameraEffects(void)
	: m_iAngle(-90)
	, m_bStatusBloodScreen(false)
	, m_CameraEffects_BloodyScreen(NULL)
	, m_fCountdownTimer_BloodScreen(2.0f)
	, m_CameraEffects_HealthScreen(NULL)
	, m_fCountdownTimer_HealthScreen(2.0f)
	, mode(MODE_2D)
{
	Init();
}
CCameraEffects::~CCameraEffects(void)
{
	if (m_CameraEffects_BloodyScreen)
	{
		delete m_CameraEffects_BloodyScreen;
		m_CameraEffects_BloodyScreen = NULL;
	}
	if (m_CameraEffects_HealthScreen)
	{
		delete m_CameraEffects_HealthScreen;
		m_CameraEffects_HealthScreen = NULL;
	}
}

// Initialise this class instance
bool CCameraEffects::Init(void)
{
	m_iAngle = -90;
	position.Set(0.0f, 0.0f, 0.0f);
	scale.Set(800.0f, 600.0f, 100.0f);

	return true;
}

bool CCameraEffects::SetBloodScreen(Mesh* aBloodScreen)
{
	if(aBloodScreen != NULL)
	{
		m_CameraEffects_BloodyScreen = aBloodScreen;
		return true;
	}
	return false;
}
Mesh* CCameraEffects::GetBloodScreen(void) const
{
	return m_CameraEffects_BloodyScreen;
}

bool CCameraEffects::SetHealthScreen(Mesh* aHealthScreen)
{
	if (aHealthScreen != NULL)
	{
		m_CameraEffects_HealthScreen = aHealthScreen;
		return true;
	}
	return false;
}
Mesh* CCameraEffects::GetHealthScreen(void) const
{
	return m_CameraEffects_HealthScreen;
}

// Set m_iAngle of avatar
bool CCameraEffects::SetAngle(const int m_iAngle)
{
	this->m_iAngle = m_iAngle;
	return true;
}
// Get m_iAngle
int CCameraEffects::GetAngle(void) const
{
	return m_iAngle;
}

// Set boolean flag for BloodScreen
bool CCameraEffects::SetStatus_BloodScreen(const bool m_bStatusBloodScreen)
{
	this->m_bStatusBloodScreen = m_bStatusBloodScreen;
	return true;
}

// Set Countdown Timer for BloodScreen
bool CCameraEffects::SetTimer_BloodScreen(const float m_fCountdownTimer_BloodScreen)
{
	this->m_fCountdownTimer_BloodScreen = m_fCountdownTimer_BloodScreen;
	return true;
}

// Get Countdown Timer for BloodScreen
float CCameraEffects::GetTimer_BloodScreen(void) const
{
	return m_fCountdownTimer_BloodScreen;
}


bool CCameraEffects::SetStatus_HealthScreen(const bool m_bStatusHealthScreen)
{
	this->m_bStatusHealthScreen = m_bStatusHealthScreen;
	return true;
}

bool CCameraEffects::SetTimer_HealthScreen(const float m_fCountdownTimer_HealthScreen)
{
	this->m_fCountdownTimer_HealthScreen = m_fCountdownTimer_HealthScreen;
	return true;
}


float CCameraEffects::GetTimer_HealthScreen(void) const
{
	return m_fCountdownTimer_HealthScreen;
}

// Update the camera effects
void CCameraEffects::Update(const float dt)
{
	if (m_bStatusBloodScreen)
	{
		m_fCountdownTimer_BloodScreen -= dt;
		if (m_fCountdownTimer_BloodScreen <= 0.0f)
		{
			// Set the bool flag for Render BloodScreen to false
			m_bStatusBloodScreen = false;
			// Reset the countdown timer to the default value
			m_fCountdownTimer_BloodScreen = 2.0f;
		}
	}

	if (m_bStatusHealthScreen)
	{
		m_fCountdownTimer_HealthScreen -= dt;
		if (m_fCountdownTimer_HealthScreen <= 0.0f)
		{
			// Set the bool flag for Render BloodScreen to false
			m_bStatusHealthScreen = false;
			// Reset the countdown timer to the default value
			m_fCountdownTimer_HealthScreen = 2.0f;
		}
	}
}

// Render the UI
void CCameraEffects::RenderUI()
{
	if (mode == MODE_3D)
		return;

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();

	// Push the current transformation into the modelStack
	modelStack.PushMatrix();
		// Translate the current transformation
		modelStack.Translate(position.x, position.y, position.z);
		// Scale the current transformation
		modelStack.Scale(scale.x, scale.y, scale.z);

		// Push the current transformation into the modelStack
		modelStack.PushMatrix();
			// Display the Avatar
			if ((m_bStatusBloodScreen) && (m_CameraEffects_BloodyScreen))
			{
				RenderHelper::RenderMesh(m_CameraEffects_BloodyScreen);
			}
			else if ((m_bStatusHealthScreen) && (m_CameraEffects_HealthScreen))
			{
				RenderHelper::RenderMesh(m_CameraEffects_HealthScreen);
			}
		modelStack.PopMatrix();

	modelStack.PopMatrix();

}

CCameraEffects* Create::CameraEffects(const bool m_bAddToLibrary)
{
	CCameraEffects* result = CCameraEffects::GetInstance();
	if (m_bAddToLibrary)
		EntityManager::GetInstance()->AddEntity(result);
	return result;
}
