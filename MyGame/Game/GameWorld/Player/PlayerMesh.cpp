//
// PlayerMesh.cpp
// Actor: Tamamura Shuuki
//

#include "PlayerMesh.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pGameObject">このコンポーネントを所持しているゲームオブジェクト</param>
PlayerMesh::PlayerMesh(GameObject* pGameObject):
	Mesh(pGameObject),
	m_pConstBuffer0(nullptr),
	m_pConstBuffer1(nullptr),
	m_pConstBuffer2(nullptr),
	m_pProperty(nullptr),
	m_pCommonStates(nullptr),
	m_destruction(0)
{
	Create();
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerMesh::~PlayerMesh()
{
	SAFE_RELEASE(m_pConstBuffer0);
	SAFE_RELEASE(m_pConstBuffer1);
	SAFE_RELEASE(m_pConstBuffer2);
	SAFE_RELEASE(m_pProperty);
}

/// <summary>
/// 作成
/// </summary>
void PlayerMesh::Create()
{
	DeviceResources* pDeviceResources = DeviceResources::GetInstance();
	auto device = pDeviceResources->GetD3DDevice();

	HRESULT hr;

	// シェーダーを作成
	hr = CreateShaderFromCSO(L"Resources\\Shaders\\PlayerVS.cso", L"Resources\\Shaders\\PlayerGS.cso", L"Resources\\Shaders\\PlayerPS.cso");
	if (FAILED(hr))
	{
		MessageBox(0, L"シェーダーの作成に失敗しました。", NULL, MB_OK);
		return;
	}

	// メッシュを作成
	hr = CreateMeshFromOBJ(L"Resources\\Models\\Sphere.obj");
	if (FAILED(hr))
	{
		MessageBox(0, L"メッシュの作成に失敗しました。", NULL, MB_OK);
		return;
	}

	// 定数バッファを作成
	// 定数バッファを作成する
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = 0;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DEFAULT;
	// バッファ0
	cb.ByteWidth = sizeof(ConstBuffer0);
	hr = device->CreateBuffer(&cb, NULL, &m_pConstBuffer0);
	if (FAILED(hr)) return;
	// バッファ1
	cb.ByteWidth = sizeof(ConstBuffer1);
	hr = device->CreateBuffer(&cb, NULL, &m_pConstBuffer1);
	if (FAILED(hr)) return;
	// バッファ2
	cb.ByteWidth = sizeof(ConstBuffer2);
	hr = device->CreateBuffer(&cb, NULL, &m_pConstBuffer2);
	if (FAILED(hr)) return;
	// バッファ3(プロパティ)
	cb.ByteWidth = sizeof(Property);
	hr = device->CreateBuffer(&cb, NULL, &m_pProperty);
	if (FAILED(hr)) return;

	// コモンステートの作成
	m_pCommonStates = std::make_unique<CommonStates>(device);
}

/// <summary>
/// 描画
/// </summary>
void PlayerMesh::Draw()
{
	DeviceResources* pDeviceResources = DeviceResources::GetInstance();
	auto context = pDeviceResources->GetD3DDeviceContext();

	// 描画情報を設定
	context->OMSetBlendState(m_pCommonStates->NonPremultiplied(), nullptr, 0xffffffff);
	context->OMSetDepthStencilState(m_pCommonStates->DepthDefault(), 0);
	context->RSSetState(m_pCommonStates->CullNone());

	// このメッシュコンポーネントを所持しているオブジェクトのモデル行列
	Camera* pCamera = Camera::GetMain()->GetComponent<Camera>();
	Matrix world = m_pTransform->GetWorld();
	Matrix view = pCamera->GetView();
	Matrix projection = pCamera->GetProjection();

	// ワールドから射影までの変換行列を作成
	Matrix wvp = world * view * projection;

	// シェーダの定数バッファに各種データを渡す
	// バッファ0
	ConstBuffer0 cb0;
	cb0.world = world.Transpose();
	cb0.view = view.Transpose();
	cb0.proj = projection.Transpose();
	cb0.wvp = wvp.Transpose();
	context->UpdateSubresource(m_pConstBuffer0, 0, NULL, &cb0, 0, 0);
	// バッファ1
	ConstBuffer1 cb1;
	cb1.diffuse = Vector4(1, 1, 1, 1);
	cb1.ambient = Vector4(1, 1, 1, 1);
	cb1.specular = Vector4(1, 1, 1, 1);
	cb1.lightPos = Vector4(0, 1, -1, 1);
	Vector3 eye = pCamera->GetTransform()->GetPosition();
	cb1.cameraPos = Vector4(eye.x, eye.y, eye.z, 1);
	context->UpdateSubresource(m_pConstBuffer1, 0, NULL, &cb1, 0, 0);
	// バッファ2
	ConstBuffer2 cb2;
	float time = Time::GetInstance()->GetTotalTime();
	cb2.time = time;
	cb2.sinTime = sin(time);
	cb2.cosTime = cos(time);
	context->UpdateSubresource(m_pConstBuffer2, 0, NULL, &cb2, 0, 0);
	// バッファ3(プロパティ)
	m_callOnDestruction();
	Property cb3;
	cb3.destruction = m_destruction;
	context->UpdateSubresource(m_pProperty, 0, NULL, &cb3, 0, 0);

	// 使用するシェーダーの登録
	context->VSSetShader(m_pVertexShader, NULL, 0);
	context->PSSetShader(m_pPixelShader, NULL, 0);
	context->GSSetShader(m_pGeometryShader, NULL, 0);

	// 作成した定数バッファを、使用するシェーダに設定
	context->VSSetConstantBuffers(0, 1, &m_pConstBuffer0);
	context->GSSetConstantBuffers(0, 1, &m_pConstBuffer0);
	context->PSSetConstantBuffers(0, 1, &m_pConstBuffer0);
	context->VSSetConstantBuffers(1, 1, &m_pConstBuffer1);
	context->GSSetConstantBuffers(1, 1, &m_pConstBuffer1);
	context->PSSetConstantBuffers(1, 1, &m_pConstBuffer1);
	context->VSSetConstantBuffers(2, 1, &m_pConstBuffer2);
	context->GSSetConstantBuffers(2, 1, &m_pConstBuffer2);
	context->PSSetConstantBuffers(2, 1, &m_pConstBuffer2);
	context->VSSetConstantBuffers(3, 1, &m_pProperty);
	context->GSSetConstantBuffers(3, 1, &m_pProperty);
	context->PSSetConstantBuffers(3, 1, &m_pProperty);

	// 頂点バッファをセット
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// 入力レイアウトをセット
	context->IASetInputLayout(m_pInputLayout);

	// プリミティブ・トポロジーをセット
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// プリミティブをレンダリング
	context->Draw(m_vertexCount, 0);
}

/// <summary>
/// 破壊処理を呼び出す
/// </summary>
void PlayerMesh::CallOnDestruction()
{
	// 破壊処理を登録する
	m_callOnDestruction = ([=]{
		m_destruction += Time::GetInstance()->GetElapsedTime()*5;

		if (m_destruction >= 1)
		{
			m_destruction = 1;
		}
	});
}
