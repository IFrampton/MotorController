#include "SineTable.h"

float SineTable::_sineTableFactor = (float)(sizeof(_sineTable) / sizeof(float) - 1.0f) / 360.0f; // Note: this is used to increase speed
float SineTable::_sineTable[513] =
{
		0.0f,
		0.012271538f,
		0.024541229f,
		0.036807223f,
		0.049067674f,
		0.061320736f,
		0.073564564f,
		0.085797312f,
		0.09801714f,
		0.110222207f,
		0.122410675f,
		0.134580709f,
		0.146730474f,
		0.158858143f,
		0.170961889f,
		0.183039888f,
		0.195090322f,
		0.207111376f,
		0.21910124f,
		0.231058108f,
		0.24298018f,
		0.25486566f,
		0.266712757f,
		0.278519689f,
		0.290284677f,
		0.302005949f,
		0.31368174f,
		0.325310292f,
		0.336889853f,
		0.34841868f,
		0.359895037f,
		0.371317194f,
		0.382683432f,
		0.39399204f,
		0.405241314f,
		0.41642956f,
		0.427555093f,
		0.438616239f,
		0.44961133f,
		0.460538711f,
		0.471396737f,
		0.482183772f,
		0.492898192f,
		0.503538384f,
		0.514102744f,
		0.524589683f,
		0.53499762f,
		0.545324988f,
		0.555570233f,
		0.565731811f,
		0.575808191f,
		0.585797857f,
		0.595699304f,
		0.605511041f,
		0.615231591f,
		0.624859488f,
		0.634393284f,
		0.643831543f,
		0.653172843f,
		0.662415778f,
		0.671558955f,
		0.680600998f,
		0.689540545f,
		0.698376249f,
		0.707106781f,
		0.715730825f,
		0.724247083f,
		0.732654272f,
		0.740951125f,
		0.749136395f,
		0.757208847f,
		0.765167266f,
		0.773010453f,
		0.780737229f,
		0.788346428f,
		0.795836905f,
		0.803207531f,
		0.810457198f,
		0.817584813f,
		0.824589303f,
		0.831469612f,
		0.838224706f,
		0.844853565f,
		0.851355193f,
		0.85772861f,
		0.863972856f,
		0.870086991f,
		0.876070094f,
		0.881921264f,
		0.88763962f,
		0.893224301f,
		0.898674466f,
		0.903989293f,
		0.909167983f,
		0.914209756f,
		0.919113852f,
		0.923879533f,
		0.92850608f,
		0.932992799f,
		0.937339012f,
		0.941544065f,
		0.945607325f,
		0.949528181f,
		0.95330604f,
		0.956940336f,
		0.960430519f,
		0.963776066f,
		0.966976471f,
		0.970031253f,
		0.972939952f,
		0.97570213f,
		0.978317371f,
		0.98078528f,
		0.983105487f,
		0.985277642f,
		0.987301418f,
		0.98917651f,
		0.990902635f,
		0.992479535f,
		0.99390697f,
		0.995184727f,
		0.996312612f,
		0.997290457f,
		0.998118113f,
		0.998795456f,
		0.999322385f,
		0.999698819f,
		0.999924702f,
		1.0f,
		0.999924702f,
		0.999698819f,
		0.999322385f,
		0.998795456f,
		0.998118113f,
		0.997290457f,
		0.996312612f,
		0.995184727f,
		0.99390697f,
		0.992479535f,
		0.990902635f,
		0.98917651f,
		0.987301418f,
		0.985277642f,
		0.983105487f,
		0.98078528f,
		0.978317371f,
		0.97570213f,
		0.972939952f,
		0.970031253f,
		0.966976471f,
		0.963776066f,
		0.960430519f,
		0.956940336f,
		0.95330604f,
		0.949528181f,
		0.945607325f,
		0.941544065f,
		0.937339012f,
		0.932992799f,
		0.92850608f,
		0.923879533f,
		0.919113852f,
		0.914209756f,
		0.909167983f,
		0.903989293f,
		0.898674466f,
		0.893224301f,
		0.88763962f,
		0.881921264f,
		0.876070094f,
		0.870086991f,
		0.863972856f,
		0.85772861f,
		0.851355193f,
		0.844853565f,
		0.838224706f,
		0.831469612f,
		0.824589303f,
		0.817584813f,
		0.810457198f,
		0.803207531f,
		0.795836905f,
		0.788346428f,
		0.780737229f,
		0.773010453f,
		0.765167266f,
		0.757208847f,
		0.749136395f,
		0.740951125f,
		0.732654272f,
		0.724247083f,
		0.715730825f,
		0.707106781f,
		0.698376249f,
		0.689540545f,
		0.680600998f,
		0.671558955f,
		0.662415778f,
		0.653172843f,
		0.643831543f,
		0.634393284f,
		0.624859488f,
		0.615231591f,
		0.605511041f,
		0.595699304f,
		0.585797857f,
		0.575808191f,
		0.565731811f,
		0.555570233f,
		0.545324988f,
		0.53499762f,
		0.524589683f,
		0.514102744f,
		0.503538384f,
		0.492898192f,
		0.482183772f,
		0.471396737f,
		0.460538711f,
		0.44961133f,
		0.438616239f,
		0.427555093f,
		0.41642956f,
		0.405241314f,
		0.39399204f,
		0.382683432f,
		0.371317194f,
		0.359895037f,
		0.34841868f,
		0.336889853f,
		0.325310292f,
		0.31368174f,
		0.302005949f,
		0.290284677f,
		0.278519689f,
		0.266712757f,
		0.25486566f,
		0.24298018f,
		0.231058108f,
		0.21910124f,
		0.207111376f,
		0.195090322f,
		0.183039888f,
		0.170961889f,
		0.158858143f,
		0.146730474f,
		0.134580709f,
		0.122410675f,
		0.110222207f,
		0.09801714f,
		0.085797312f,
		0.073564564f,
		0.061320736f,
		0.049067674f,
		0.036807223f,
		0.024541229f,
		0.012271538f,
		1.22515E-16f,
		-0.012271538f,
		-0.024541229f,
		-0.036807223f,
		-0.049067674f,
		-0.061320736f,
		-0.073564564f,
		-0.085797312f,
		-0.09801714f,
		-0.110222207f,
		-0.122410675f,
		-0.134580709f,
		-0.146730474f,
		-0.158858143f,
		-0.170961889f,
		-0.183039888f,
		-0.195090322f,
		-0.207111376f,
		-0.21910124f,
		-0.231058108f,
		-0.24298018f,
		-0.25486566f,
		-0.266712757f,
		-0.278519689f,
		-0.290284677f,
		-0.302005949f,
		-0.31368174f,
		-0.325310292f,
		-0.336889853f,
		-0.34841868f,
		-0.359895037f,
		-0.371317194f,
		-0.382683432f,
		-0.39399204f,
		-0.405241314f,
		-0.41642956f,
		-0.427555093f,
		-0.438616239f,
		-0.44961133f,
		-0.460538711f,
		-0.471396737f,
		-0.482183772f,
		-0.492898192f,
		-0.503538384f,
		-0.514102744f,
		-0.524589683f,
		-0.53499762f,
		-0.545324988f,
		-0.555570233f,
		-0.565731811f,
		-0.575808191f,
		-0.585797857f,
		-0.595699304f,
		-0.605511041f,
		-0.615231591f,
		-0.624859488f,
		-0.634393284f,
		-0.643831543f,
		-0.653172843f,
		-0.662415778f,
		-0.671558955f,
		-0.680600998f,
		-0.689540545f,
		-0.698376249f,
		-0.707106781f,
		-0.715730825f,
		-0.724247083f,
		-0.732654272f,
		-0.740951125f,
		-0.749136395f,
		-0.757208847f,
		-0.765167266f,
		-0.773010453f,
		-0.780737229f,
		-0.788346428f,
		-0.795836905f,
		-0.803207531f,
		-0.810457198f,
		-0.817584813f,
		-0.824589303f,
		-0.831469612f,
		-0.838224706f,
		-0.844853565f,
		-0.851355193f,
		-0.85772861f,
		-0.863972856f,
		-0.870086991f,
		-0.876070094f,
		-0.881921264f,
		-0.88763962f,
		-0.893224301f,
		-0.898674466f,
		-0.903989293f,
		-0.909167983f,
		-0.914209756f,
		-0.919113852f,
		-0.923879533f,
		-0.92850608f,
		-0.932992799f,
		-0.937339012f,
		-0.941544065f,
		-0.945607325f,
		-0.949528181f,
		-0.95330604f,
		-0.956940336f,
		-0.960430519f,
		-0.963776066f,
		-0.966976471f,
		-0.970031253f,
		-0.972939952f,
		-0.97570213f,
		-0.978317371f,
		-0.98078528f,
		-0.983105487f,
		-0.985277642f,
		-0.987301418f,
		-0.98917651f,
		-0.990902635f,
		-0.992479535f,
		-0.99390697f,
		-0.995184727f,
		-0.996312612f,
		-0.997290457f,
		-0.998118113f,
		-0.998795456f,
		-0.999322385f,
		-0.999698819f,
		-0.999924702f,
		-1.0f,
		-0.999924702f,
		-0.999698819f,
		-0.999322385f,
		-0.998795456f,
		-0.998118113f,
		-0.997290457f,
		-0.996312612f,
		-0.995184727f,
		-0.99390697f,
		-0.992479535f,
		-0.990902635f,
		-0.98917651f,
		-0.987301418f,
		-0.985277642f,
		-0.983105487f,
		-0.98078528f,
		-0.978317371f,
		-0.97570213f,
		-0.972939952f,
		-0.970031253f,
		-0.966976471f,
		-0.963776066f,
		-0.960430519f,
		-0.956940336f,
		-0.95330604f,
		-0.949528181f,
		-0.945607325f,
		-0.941544065f,
		-0.937339012f,
		-0.932992799f,
		-0.92850608f,
		-0.923879533f,
		-0.919113852f,
		-0.914209756f,
		-0.909167983f,
		-0.903989293f,
		-0.898674466f,
		-0.893224301f,
		-0.88763962f,
		-0.881921264f,
		-0.876070094f,
		-0.870086991f,
		-0.863972856f,
		-0.85772861f,
		-0.851355193f,
		-0.844853565f,
		-0.838224706f,
		-0.831469612f,
		-0.824589303f,
		-0.817584813f,
		-0.810457198f,
		-0.803207531f,
		-0.795836905f,
		-0.788346428f,
		-0.780737229f,
		-0.773010453f,
		-0.765167266f,
		-0.757208847f,
		-0.749136395f,
		-0.740951125f,
		-0.732654272f,
		-0.724247083f,
		-0.715730825f,
		-0.707106781f,
		-0.698376249f,
		-0.689540545f,
		-0.680600998f,
		-0.671558955f,
		-0.662415778f,
		-0.653172843f,
		-0.643831543f,
		-0.634393284f,
		-0.624859488f,
		-0.615231591f,
		-0.605511041f,
		-0.595699304f,
		-0.585797857f,
		-0.575808191f,
		-0.565731811f,
		-0.555570233f,
		-0.545324988f,
		-0.53499762f,
		-0.524589683f,
		-0.514102744f,
		-0.503538384f,
		-0.492898192f,
		-0.482183772f,
		-0.471396737f,
		-0.460538711f,
		-0.44961133f,
		-0.438616239f,
		-0.427555093f,
		-0.41642956f,
		-0.405241314f,
		-0.39399204f,
		-0.382683432f,
		-0.371317194f,
		-0.359895037f,
		-0.34841868f,
		-0.336889853f,
		-0.325310292f,
		-0.31368174f,
		-0.302005949f,
		-0.290284677f,
		-0.278519689f,
		-0.266712757f,
		-0.25486566f,
		-0.24298018f,
		-0.231058108f,
		-0.21910124f,
		-0.207111376f,
		-0.195090322f,
		-0.183039888f,
		-0.170961889f,
		-0.158858143f,
		-0.146730474f,
		-0.134580709f,
		-0.122410675f,
		-0.110222207f,
		-0.09801714f,
		-0.085797312f,
		-0.073564564f,
		-0.061320736f,
		-0.049067674f,
		-0.036807223f,
		-0.024541229f,
		-0.012271538f,
		0.0f
};
