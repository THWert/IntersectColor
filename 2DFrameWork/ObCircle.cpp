#include "framework.h"
ID3D11Buffer* ObCircle::fillVertexBuffer = nullptr;
ID3D11Buffer* ObCircle::vertexBuffer = nullptr;

void ObCircle::CreateStaticMember()
{
    VertexPC* Vertex;
    Vertex = new VertexPC[360 * 3];

    for (UINT i = 0; i < 360; i++)
    {
        Vertex[i * 3].position.x = 0.0f;
        Vertex[i * 3].position.y = 0.0f;
        Vertex[i * 3].color = Color(0.333f, 0.333f, 0.333f, 1.0f);
        //Vertex[i * 3].color = Color(RANDOM->Float(), RANDOM->Float(), RANDOM->Float(), 1.0f);

        //0 1 2 ... 359
        Vertex[i * 3 + 1].position.x = cosf(i * ToRadian) * 0.5f;
        Vertex[i * 3 + 1].position.y = sinf(i * ToRadian) * 0.5f;
        //Vertex[i * 3 + 1].color = Color(0.0f, 0.0f, 0.0f, 1.0f);
        //Vertex[i * 3 + 1].color = Color(RANDOM->Float(), RANDOM->Float(), RANDOM->Float(), 1.0f);

        //1 2 3 .. 360
        Vertex[i * 3 + 2].position.x = cosf((i + 1) * ToRadian) * 0.5f;
        Vertex[i * 3 + 2].position.y = sinf((i + 1) * ToRadian) * 0.5f;
        //Vertex[i * 3 + 2].color = Color(0.0f, 0.0f, 0.0f, 1.0f);
        //Vertex[i * 3 + 2].color = Color(RANDOM->Float(), RANDOM->Float(), RANDOM->Float(), 1.0f);
    
        if (i < 120)
        {
            float color1 = i / 120.0f;
            float color2 = (i + 1) / 120.0f;

            Vertex[i * 3 + 1].color = Color(1.0f - color1, color1, 0.0f, 1.0f);
            Vertex[i * 3 + 2].color = Color(1.0f - color2, color2, 0.0f, 1.0f);
        }
        else if (i < 240)
        {
            float color1 = (i - 120) / 120.0f;
            float color2 = (i - 120 + 1) / 120.0f;

            Vertex[i * 3 + 1].color = Color(0.0f, 1.0f - color1, color1, 1.0f);
            Vertex[i * 3 + 2].color = Color(0.0f, 1.0f - color2, color2, 1.0f);
        }
        else
        {
            float color1 = (i - 240) / 120.0f;
            float color2 = (i - 240 + 1) / 120.0f;

            Vertex[i * 3 + 1].color = Color(color1, 0.0f, 1.0f - color1, 1.0f);
            Vertex[i * 3 + 2].color = Color(color2, 0.0f, 1.0f - color2, 1.0f);
        }
    
    
    }
    //???????? ?????? ???????? ????
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 }; //???????? ???? 0????
        desc.Usage = D3D11_USAGE_DEFAULT;//?????? ???? ???? ????
        desc.ByteWidth = sizeof(VertexPC) * 360 * 3; //???? ???? (??????)??????.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//?????? ?????? ?????? ?????????? ?????? ????????????

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //???? ???????? ?????????????? ???????? ??????????.
        data.pSysMem = Vertex;
        //?????? ???????? ??????.

        //???? ??????
        //                                           ????    ????       ????????   
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &fillVertexBuffer);
        assert(SUCCEEDED(hr));

    }

    delete[] Vertex;

    Vertex = new VertexPC[361];

    //?????? ?????? ?? ??????
    for (UINT i = 0; i < 361; i++)
    {
        Vertex[i].color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        Vertex[i].position.x = cosf(i * ToRadian) * 0.5f;
        Vertex[i].position.y = sinf(i * ToRadian) * 0.5f;
    }


    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//?????? ???? ???? ????
        desc.ByteWidth = sizeof(VertexPC) * 361; //???? ???? (??????)??????.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//?????? ?????? ?????? ?????????? ?????? ????????????

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //???? ???????? ?????????????? ???????? ??????????.
        data.pSysMem = Vertex;
        //?????? ???????? ??????.

        //???? ??????
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
        assert(SUCCEEDED(hr));

    }
    delete[] Vertex;
}

void ObCircle::DeleteStaticMember()
{
    vertexBuffer->Release();
    fillVertexBuffer->Release();
}

ObCircle::ObCircle()
{
    collision = COLLIDER::CIRCLE;
}

void ObCircle::Render()
{
    if (!isVisible)return;
    GameObject::Render();

    basicShader->Set();

    UINT stride = sizeof(VertexPC);
    UINT offset = 0;

    if (isFilled)
    {
        D3D->GetDC()->IASetVertexBuffers(0,
            1,
            &fillVertexBuffer,
            &stride,
            &offset);
        D3D->GetDC()->IASetPrimitiveTopology
        (D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        D3D->GetDC()->Draw(360 * 3, 0);
    }
    else
    {
        D3D->GetDC()->IASetVertexBuffers(0,//????????(16~32?????? ????????)
            1,//?????????? ???????? ???? ?????? ????
            &vertexBuffer,
            &stride,//?????????? ?? ?????? ?????????? ????
            &offset);
        D3D->GetDC()->IASetPrimitiveTopology
        (D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
        D3D->GetDC()->Draw(361, 0);
    }
}

