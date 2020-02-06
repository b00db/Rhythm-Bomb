
// rythm01View.cpp: Crythm01View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "rythm01.h"
#endif

#include "rythm01Doc.h"
#include "rythm01View.h"
#include <iostream>

#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Crythm01View

IMPLEMENT_DYNCREATE(Crythm01View, CView)

BEGIN_MESSAGE_MAP(Crythm01View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// Crythm01View 생성/소멸

Crythm01View::Crythm01View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

	next = 0;
	nextbuf = 0;
	cha.x = 0, cha.y = 0;
	count = 0;
	rank = 0;
	page = 0;
	melody_no = -1;
	selectpage = 0;
	mode = 0;
}

Crythm01View::~Crythm01View()
{
}

BOOL Crythm01View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// Crythm01View 그리기

void Crythm01View::OnDraw(CDC* pDC)
{
	Crythm01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	
	switch (page) {
	case 0:
		StartPage();
		break;
	case 1:
		SongSelectPage();
		break;
	case 3:
		RankPage();
		break;
	case 2:


		int x, y, px, py, ex, ey;
		int start_x = 50, start_y = 50;
		int width = 150;



		CBrush whitebrush;
		int row, col;

		px = start_x;
		py = start_y;

		ex = start_x + width * 5;
		ey = start_y + width * 5;


		//색 지정
		whitebrush.CreateSolidBrush(RGB(255, 255, 255));


		CBitmap bgtest, whiteblock, greenblock, yellowblock, orangeblock, redblock, bitcharic, bitbang, bitheart1, bitheart2, *poldpng, *pold;
		CDC mDC, mDC1;
		mDC.CreateCompatibleDC(pDC);
		mDC1.CreateCompatibleDC(pDC);

		whiteblock.LoadBitmap(IDB_WIITE);
		greenblock.LoadBitmap(IDB_GREEN);
		yellowblock.LoadBitmap(IDB_YELLOW);
		orangeblock.LoadBitmap(IDB_ORANGE);
		redblock.LoadBitmap(IDB_RED);
		bitcharic.LoadBitmap(IDB_CHA);
		bitbang.LoadBitmap(IDB_BANG);
		bitheart1.LoadBitmap(IDB_HEART);
		bitheart2.LoadBitmap(IDB_BROKEN);
		bgtest.LoadBitmap(IDB_BGTEST);
		/*
		// 화이트 브러쉬 객체 등록 및 이전 브러쉬 저장.
		poldbrush = mDC.SelectObject(&whitebrush);
		// 화이트 브러쉬를 이용하여 사각형 그래픽 출력.
		mDC.Rectangle(px, py, ex, ey);
		// 이전 브러쉬 객체로 등록.
		mDC.SelectObject(pold);*/
		pold = mDC.SelectObject(&bgtest);
		//BG출력
		mDC1.SelectObject(&bgtest);
		mDC.BitBlt(0, 0, 1280, 800, &mDC1, 0, 0, SRCCOPY);
		mDC1.SelectObject(pold);


		//칸돌리기
		for (col = 0; col < 5; col++)
			for (row = 0; row < 5; row++) {
				// 칸의 시작 좌표.
				px = row * width + 50;
				py = col * width + 50;
				// 칸의 끝 좌표.
				ex = row * width + 200;
				ey = col * width + 200;

				switch (pan[col][row]) {
				case 0:  // 하얀색 칸.
					mDC1.SelectObject(&whiteblock);
					mDC.TransparentBlt(px, py, 150, 150, &mDC1, 0, 0, 150, 150, RGB(0, 0, 0));

					break;
				case 1:  // 초록색 칸.
					mDC1.SelectObject(&greenblock);
					mDC.TransparentBlt(px, py, 150, 150, &mDC1, 0, 0, 150, 150, RGB(255, 255, 255));

					break;
				case 2:  // 노란색 칸.
					mDC1.SelectObject(&yellowblock);
					mDC.TransparentBlt(px, py, 150, 150, &mDC1, 0, 0, 150, 150, RGB(255, 255, 255));

					break;
				case 3:  // 주황색 칸.
					mDC1.SelectObject(&orangeblock);
					mDC.TransparentBlt(px, py, 150, 150, &mDC1, 0, 0, 150, 150, RGB(255, 255, 255));

					break;
				case 4:  // 빨간색 칸.
					mDC1.SelectObject(&redblock);
					mDC.TransparentBlt(px, py, 150, 150, &mDC1, 0, 0, 150, 150, RGB(255, 255, 255));

					break;
				case 5:
					mDC1.SelectObject(&bitbang);
					mDC.TransparentBlt(px, py, 150, 150, &mDC1, 0, 0, 150, 150, RGB(255, 255, 255));


				}


			}

		poldpng = mDC1.SelectObject(&bitcharic);
		mDC.TransparentBlt(50 + cha.x * 150, 50 + cha.y * 150, 150, 150, &mDC1, 0, 0, 100, 100, RGB(255, 255, 255));


		switch (power) {
		case 3:
			for (int q = 0; q < 3; q++)
			{
				mDC1.SelectObject(&bitheart1);
				mDC.TransparentBlt(900 + q * 100, 700, 75, 75, &mDC1, 0, 0, 75, 75, RGB(255, 255, 255));

			}

			break;

		case 2:
			for (int q = 0; q < 2; q++)
			{
				mDC1.SelectObject(&bitheart1);
				mDC.TransparentBlt(900 + q * 100, 700, 75, 75, &mDC1, 0, 0, 75, 75, RGB(255, 255, 255));

			}

			mDC1.SelectObject(&bitheart2);
			mDC.TransparentBlt(1100, 700, 75, 75, &mDC1, 0, 0, 75, 75, RGB(255, 255, 255));


			break;

		case 1:
			mDC1.SelectObject(&bitheart1);
			mDC.TransparentBlt(900, 700, 75, 75, &mDC1, 0, 0, 75, 75, RGB(255, 255, 255));


			for (int q = 0; q < 2; q++) {
				mDC1.SelectObject(&bitheart2);
				mDC.TransparentBlt(1000 + q * 100, 700, 75, 75, &mDC1, 0, 0, 75, 75, RGB(255, 255, 255));


			}
			break;

		case 0:
			for (int q = 0; q < 3; q++) {
				mDC1.SelectObject(&bitheart2);
				mDC.TransparentBlt(900 + q * 100, 700, 75, 75, &mDC1, 0, 0, 75, 75, RGB(255, 255, 255));


			}
			break;
		}



		for (x = 0; x < 6; x++) {
			px = start_x + x * width;
			py = start_y;
			ex = px;
			ey = py + width * 5;
			mDC.MoveTo(px, py);
			mDC.LineTo(ex, ey);

		}

		for (y = 0; y < 6; y++) {
			px = start_x;
			py = start_y + y * width;
			ex = start_x + width * 5;
			ey = py;
			mDC.MoveTo(px, py);
			mDC.LineTo(ex, ey);
		}
		pDC->BitBlt(0, 0, 1280, 800, &mDC, 0, 0, SRCCOPY);
		mDC.SelectObject(pold);
	}
	/*
	//마우스 좌표 출력

	CString strData = _T("");
	strData.Format(_T("x=%d y=%d songpage=%d mode=%d"), m_ptMouse.x, m_ptMouse.y, melody_no, mode);
	pDC->SetTextColor(RGB(200, 200, 200));
	pDC->SetBkColor(RGB(255, 0, 0));
	pDC->TextOut(10, 10, strData);
	*/
}

// Crythm01View 인쇄

BOOL Crythm01View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void Crythm01View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void Crythm01View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// Crythm01View 진단

#ifdef _DEBUG
void Crythm01View::AssertValid() const
{
	CView::AssertValid();
}

void Crythm01View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Crythm01Doc* Crythm01View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Crythm01Doc)));
	return (Crythm01Doc*)m_pDocument;
}
#endif //_DEBUG


// Crythm01View 메시지 처리기


void Crythm01View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/* 잘보고 바꾸자-!
	*/
	switch (nChar) {
		//상,하,좌,우 캐릭터 움직임
	case VK_UP:
		if (cha.y != 0) cha.y -= 1;
		break;
	case VK_DOWN:
		if (cha.y != 4) cha.y += 1;
		break;
	case VK_LEFT:
		if (cha.x != 0) cha.x -= 1;
		break;
	case VK_RIGHT:
		if (cha.x != 4) cha.x += 1;
		break;
		//게임 플레이화면 나가기
	case VK_ESCAPE:
		KillTimer(1);
		PlaySound(NULL, NULL, NULL);
		if (page == 2) {
			page = 1;
		}
		break;
	}

	if (cha.x < 0)
	{
		cha.x = 0;
		AfxMessageBox(_T("왼 쪽 으로 더이상 못감."));
	}
	if (cha.y < 0)
	{
		cha.y = 0;
		AfxMessageBox(_T("위 쪽으로 더이상 못감."));
	}

	Invalidate(false);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void Crythm01View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1){
	DrawCha();
	}
	if (nIDEvent == 2) {
		PlaySound(TEXT("./res/sound/hit.wav"), NULL, SND_ASYNC);
	}
	/*if (nIDEvent == 1) {
			for (int row = 0; row < 5; row++) {
				for (int col = 0; col < 5; col++) {
					next = buf[nextbuf][row][col];
					if (pan[row][col] == 0) pan[row][col] = next;
					else if (pan[row][col] == 5) pan[row][col] = 0;
					else pan[row][col]++;
				}
			}
			NextMelody();
		}
	Invalidate(false);*/
	CView::OnTimer(nIDEvent);
	
}


void Crythm01View::OnSelectMelody()
{
	// TODO: 여기에 구현 코드 추가.
	start = true;
	switch (melody_no){
		case 1:
			SetTimer(1, 100, NULL);
			PlaySound(TEXT("./res/sound/song_overwatch_remix.wav"), NULL, SND_ASYNC);
			break;
		case 2:
			SetTimer(1, 100, NULL);
			PlaySound(TEXT("./res/sound/song_Beethoven_Virus.wav"), NULL, SND_ASYNC);
			break;
		case 3:
			SetTimer(1, 100, NULL);
			PlaySound(TEXT("./res/sound/song_Energetic.wav"), NULL, SND_ASYNC);
			break;
		case 4:
			SetTimer(1, 100, NULL);
			PlaySound(TEXT("./res/sound/song_Love_Scenario1.1.wav"), NULL, SND_ASYNC);
			break;
		case 5:
			SetTimer(1, 100, NULL);
			PlaySound(TEXT("./res/sound/song_Tribe_Attacker1.1.wav"), NULL, SND_ASYNC);
			break;
		case 6:
			SetTimer(1, 100, NULL);
			PlaySound(TEXT("./res/sound/song_Passacaglia1.1.wav"), NULL, SND_ASYNC);
			break;
		case 7:
			SetTimer(1, 100, NULL);
			PlaySound(TEXT("./res/sound/song_Destination1.2.wav"), NULL, SND_ASYNC);
			break;
		case 8:
			SetTimer(1, 100, NULL);
			PlaySound(TEXT("./res/sound/song_BBoom_BBoom1.1.wav"), NULL, SND_ASYNC);
			break;
		case 9:
			SetTimer(1, 100, NULL);
			PlaySound(TEXT("./res/sound/song_Wedding_Crashers1.1.wav"), NULL, SND_ASYNC);
			break;
		case 10:
			SetTimer(1, 100, NULL);
			PlaySound(TEXT("./res/sound/Song_Mental_Rider1.1.wav"), NULL, SND_ASYNC);
			break;
	}
}

void Crythm01View::Check_Cha()
{
	// TODO: 여기에 구현 코드 추가.

	if (pan[cha.y][cha.x] == 5) { // 캐릭터 위치가 폭발 칸.
		power--;
	}

	switch (melody_no)
	{
	case 1:
		if (nextbuf == 110) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		if (power == 0) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		break;
	case 2:
		if (nextbuf == 201) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		if (power == 0) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		break;
	case 3:
		if (nextbuf == 241) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		if (power == 0) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		break;
	case 4:
		if (nextbuf == 199) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		if (power == 0) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		break;
	case 5:
		if (nextbuf == 191) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		if (power == 0) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		break;
	case 6:
		if (nextbuf == 164) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		if (power == 0) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		break;
	case 7:
		if (nextbuf == 123) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		if (power == 0) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		break;
	case 8:
		if (nextbuf == 122) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		if (power == 0) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		break;
	case 9:
		if (nextbuf == 120) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		if (power == 0) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		break;
	case 10:
		if (nextbuf == 180) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		if (power == 0) {
			KillTimer(1);
			PlaySound(NULL, NULL, NULL);
			page++;
		}
		break;
	}
}



void Crythm01View::NextMelody()
{
	
}


void Crythm01View::DrawCha()
{
	//터지는블록 조종
	for (int row = 0; row < 5; row++) {
		for (int col = 0; col < 5; col++) {
			if (pan[row][col] == 5)
				pan[row][col] = 0;
		}
	}
	//다음블럭으로 넘어가는 시간 조종
	count++;
	if (mode == 0) {
		if (count % 10 == 0)
			for (int row = 0; row < 5; row++) {
				for (int col = 0; col < 5; col++) {
					if (pan[row][col] != 0) {
						pan[row][col]++;
					}
				}
			}
	}
	if (mode == 1 || mode == 2) {
		if (count % 5 == 0)
			for (int row = 0; row < 5; row++) {
				for (int col = 0; col < 5; col++) {
					if (pan[row][col] != 0) {
						pan[row][col]++;
					}
				}
			}
	}
	Check_Cha();
	//블럭이 나타는 시간
	switch (melody_no)
	{
	case 1:
		if (count % 5 == 0) {
			for (int row = 0; row < 5; row++) {
				for (int col = 0; col < 5; col++) {
					if (pan[row][col] == 0) {
						next = song1[nextbuf][row][col];
						if ((next == 4 && mode == 0) || (next == 4 && mode == 1)) {
							next = 1;
						}
						pan[row][col] = next;
					}
				}
			}
			nextbuf++;
		}
		break;
	case 2:
		if (count % 5 == 0) {
			for (int row = 0; row < 5; row++) {
				for (int col = 0; col < 5; col++) {
					if (pan[row][col] == 0) {
						next = song2[nextbuf][row][col];
						if ((next == 4 && mode == 0) || (next == 4 && mode == 1)) {
							next = 1;
						}
						pan[row][col] = next;
					}
				}
			}
			nextbuf++;
		}
		break;
	case 3:
		if (count % 5 == 0) {
			for (int row = 0; row < 5; row++) {
				for (int col = 0; col < 5; col++) {
					if (pan[row][col] == 0) {
						next = song3[nextbuf][row][col];
						if ((next == 4 && mode == 0) || (next == 4 && mode == 1)) {
							next = 1;
						}
						pan[row][col] = next;
					}
				}
			}
			nextbuf++;
		}
		break;
	case 4:
		if (count % 5 == 0) {
			for (int row = 0; row < 5; row++) {
				for (int col = 0; col < 5; col++) {
					if (pan[row][col] == 0) {
						next = song4[nextbuf][row][col];
						if ((next == 4 && mode == 0) || (next == 4 && mode == 1)) {
							next = 1;
						}
						pan[row][col] = next;
					}
				}
			}
			nextbuf++;
		}
		break;
	case 5:
		if (count % 5 == 0) {
			for (int row = 0; row < 5; row++) {
				for (int col = 0; col < 5; col++) {
					if (pan[row][col] == 0) {
						next = song5[nextbuf][row][col];
						if ((next == 4 && mode == 0) || (next == 4 && mode == 1)) {
							next = 1;
						}
						pan[row][col] = next;
					}
				}
			}
			nextbuf++;
		}
		break;
	case 6:
		if (count % 5 == 0) {
			for (int row = 0; row < 5; row++) {
				for (int col = 0; col < 5; col++) {
					if (pan[row][col] == 0) {
						next = song6[nextbuf][row][col];
						if ((next == 4 && mode == 0) || (next == 4 && mode == 1)) {
							next = 1;
						}
						pan[row][col] = next;
					}
				}
			}
			nextbuf++;
		}
		break;
	case 7:
		if (count % 5 == 0) {
			for (int row = 0; row < 5; row++) {
				for (int col = 0; col < 5; col++) {
					if (pan[row][col] == 0) {
						next = song7[nextbuf][row][col];
						if ((next == 4 && mode == 0) || (next == 4 && mode == 1)) {
							next = 1;
						}
						pan[row][col] = next;
					}
				}
			}
			nextbuf++;
		}
		break;
	case 8:
		if (count % 5 == 0) {
			for (int row = 0; row < 5; row++) {
				for (int col = 0; col < 5; col++) {
					if (pan[row][col] == 0) {
						next = song8[nextbuf][row][col];
						if ((next == 4 && mode == 0) || (next == 4 && mode == 1)) {
							next = 1;
						}
						pan[row][col] = next;
					}
				}
			}
			nextbuf++;
		}
		break;
	case 9:
		if (count % 5 == 0) {
			for (int row = 0; row < 5; row++) {
				for (int col = 0; col < 5; col++) {
					if (pan[row][col] == 0) {
						next = song9[nextbuf][row][col];
						if ((next == 4 && mode == 0) || (next == 4 && mode == 1)) {
							next = 1;
						}
						pan[row][col] = next;
					}
				}
			}
			nextbuf++;
		}
		break;
	case 10:
		if (count % 5 == 0) {
			for (int row = 0; row < 5; row++) {
				for (int col = 0; col < 5; col++) {
					if (pan[row][col] == 0) {
						next = song10[nextbuf][row][col];
						if ((next == 4 && mode == 0) || (next == 4 && mode == 1)) {
							next = 1;
						}
						pan[row][col] = next;
					}
				}
			}
			nextbuf++;
		}
		break;
	}

	Invalidate(false);
}


void Crythm01View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	static int x, y;
	x = m_ptMouse.x;
	y = m_ptMouse.y;

	switch (page) {
	case 0:  //StartPage()
		//게임시작
		if (x >= 390 && x <= 890 && y >= 610 && y <= 770)
		{
			page++;
			PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
			melody_no = -1;
		}
		break;

	case 1: //SongSelectPage()
		//홈버튼
		if (x >= 380 && x <= 630 && y >= 670 && y <= 770)
		{
			page--;
			PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);

		}

		//난이도 선택
		if (x >= 10 && x <= 110 && y >= 670 && y <= 770)
		{
			mode = 0;
			PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
		}
		if (x >= 110 && x <= 210 && y >= 670 && y <= 770)
		{
			mode = 1;
			PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
		}
		if (x >= 210 && x <= 310 && y >= 670 && y <= 770)
		{
			mode = 2;
			PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
		}


		//1번곡
		if (x >= 190 && x <= 490 && y >= 50 && y <= 250)
		{
			if (selectpage == 0) {
				melody_no = 1;
				SongSelectPage();
				PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
				Sleep(500);
				PlaySound(TEXT("./res/sound/sample_overwatch.wav"), NULL, SND_ASYNC | SND_LOOP);
			}
			if (selectpage == 1) {
				melody_no = 10;
				SongSelectPage();
				PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
				Sleep(500);
				PlaySound(TEXT("./res/sound/sample_Mental_Rider1.1.wav"), NULL, SND_ASYNC | SND_LOOP);
			}
		}
		//2번곡
		if (x >= 490 && x <= 790 && y >= 50 && y <= 250)
		{
			if (selectpage == 0) melody_no = 2;
			if (selectpage == 1) melody_no = 11;
			SongSelectPage();
			PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
			Sleep(500);
			PlaySound(TEXT("./res/sound/sample_Beethoven_Virus.wav"), NULL, SND_ASYNC | SND_LOOP);
		}
		
		//3번곡
		if (x >= 790 && x <= 1090 && y >= 50 && y <= 250)
		{
			if (selectpage == 0) melody_no = 3;
			if (selectpage == 1) melody_no = 12;
			SongSelectPage();
			PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
			Sleep(500);
			PlaySound(TEXT("./res/sound/sample_Energetic.wav"), NULL, SND_ASYNC | SND_LOOP);
		}
		//4번곡
		if (x >= 190 && x <= 490 && y >= 250 && y <= 450)
		{
			if (selectpage == 0) melody_no = 4;
			if (selectpage == 1) melody_no = 13;
			SongSelectPage();
			PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
			Sleep(500);
			PlaySound(TEXT("./res/sound/sample_Love_Scenario1.1.wav"), NULL, SND_ASYNC | SND_LOOP);
		}
		//5번곡
		if (x >= 490 && x <= 790 && y >= 250 && y <= 450)
		{
			if (selectpage == 0) melody_no = 5;
			if (selectpage == 1) melody_no = 14;
			SongSelectPage();
			PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
			Sleep(500);
			PlaySound(TEXT("./res/sound/sample_Tribe_Attacker1.2.wav"), NULL, SND_ASYNC | SND_LOOP);
		}
		//6번곡
		if (x >= 790 && x <= 1090 && y >= 250 && y <= 450)
		{
			if (selectpage == 0) melody_no = 6;
			if (selectpage == 1) melody_no = 15;
			SongSelectPage();
			PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
			Sleep(500);
			PlaySound(TEXT("./res/sound/sample_Passacaglia1.2.wav"), NULL, SND_ASYNC | SND_LOOP);
		}
		//7번곡
		if (x >= 190 && x <= 490 && y >= 450 && y <= 650)
		{
			if (selectpage == 0) melody_no = 7;
			if (selectpage == 1) melody_no = 16;
			SongSelectPage();
			PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
			Sleep(500);
			PlaySound(TEXT("./res/sound/sample_Destination1.2.wav"), NULL, SND_ASYNC | SND_LOOP);
		}
		//8번곡
		if (x >= 490 && x <= 790 && y >= 450 && y <= 650)
		{
			if (selectpage == 0) melody_no = 8;
			if (selectpage == 1) melody_no = 17;
			SongSelectPage();
			PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
			Sleep(500);
			PlaySound(TEXT("./res/sound/sample_BBoom_BBoom1.1.wav"), NULL, SND_ASYNC | SND_LOOP);
		}
		//9번곡
		if (x >= 790 && x <= 1090 && y >= 450 && y <= 650)
		{
			if (selectpage == 0) melody_no = 9;
			if (selectpage == 1) melody_no = 18;
			SongSelectPage();
			PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
			Sleep(500);
			PlaySound(TEXT("./res/sound/sample_Wedding_Crashers1.1.wav"), NULL, SND_ASYNC | SND_LOOP);
		}
		/*
		//10번곡
		if (x >= 596 && x <= 682 && y >= 616 && y <= 689)
		{
			melody_no = 10;
		}
		*/

		//페이지 up,down
		if (x >= 20 && x <= 164 && y >= 305 && y <= 438)
		{
			if (selectpage <= 0) selectpage = 0;
			else {
				selectpage--;
				melody_no = -1;
			}
			PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
		}
		if (x >= 1113 && x <= 1258 && y >= 305 && y <= 438)
		{
			if (selectpage >= 1) selectpage = 1;
			else {
				selectpage++;
				melody_no = -1;
			}
			PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
		}

		//노래 선택
		if (x >= 650 && x <= 900 && y >= 670 && y <= 770)
		{
			if (melody_no != -1) {
				page++;
				PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
				Sleep(300);
				OnSelectMelody();
			}
		}
		break;
	case 2:
		break;
	case 3:
		if (x >= 500 && x <= 750 && y >= 700 && y <= 800)
		{
			page = 1;
			PlaySound(TEXT("./res/sound/se_maoudamashii_system49.wav"), NULL, SND_ASYNC);
			SongSelectPage();
		}
		break;
	}

}


void Crythm01View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnMouseMove(nFlags, point);
	m_ptMouse = point;

}


void Crythm01View::StartPage()
{
	// TODO: 여기에 구현 코드 추가.
	CClientDC dc(this);

	CDC memDC,memDC1;
	CBitmap bitstart,startbtn, startbtn1, *pold;
	memDC.CreateCompatibleDC(&dc);
	memDC1.CreateCompatibleDC(&dc);

	bitstart.LoadBitmap(IDB_STARTPAGE1);
	startbtn.LoadBitmap(IDB_STARTBTN);
	startbtn1.LoadBitmap(IDB_ONSTARTBTN);

	pold = memDC.SelectObject(&bitstart);

	memDC1.SelectObject(&bitstart);
	memDC.BitBlt(0, 0, 1280, 800, &memDC1, 0, 0, SRCCOPY);

	if (m_ptMouse.x > 515 && m_ptMouse.x < 765 && m_ptMouse.y > 640 && m_ptMouse.y < 740) {
		memDC1.SelectObject(&startbtn1);
		memDC.TransparentBlt(515, 640, 250, 100, &memDC1, 0, 0, 250, 100, RGB(255, 255, 255));
	}
	else {
		memDC1.SelectObject(&startbtn);
		memDC.TransparentBlt(515, 640, 250, 100, &memDC1, 0, 0, 250, 100, RGB(255, 255, 255));
	}

	dc.BitBlt(0, 0, 1280, 800, &memDC, 0, 0, SRCCOPY);

	Invalidate(false);
	memDC.SelectObject(pold);
}


void Crythm01View::SongSelectPage()
{
	// TODO: 여기에 구현 코드 추가.
	nextbuf = 0;
	count = 0;
	power = 3;
	for (int row = 0; row < 5; row++) {
		for (int col = 0; col < 5; col++) {
			pan[row][col] = 0;
		}
	}

	CClientDC dc(this);

	CDC memDC, memDC1;
	CBitmap bitpage ,backbtn, selectbtn,backbtn1, selectbtn1, leftbtn, rightbtn, leftbtn1, rightbtn1, bitsong1, bitsong2,
		bitsong3, bitsong4, bitsong5, bitsong6, bitsong7, bitsong8, bitsong9, bitsong10, onselected, oneasymode, onmediummode, onhardmode,
		easymode, mediummode, hardmode ,*pold;
	memDC.CreateCompatibleDC(&dc);
	memDC1.CreateCompatibleDC(&dc);
	bitpage.LoadBitmap(IDB_SONGSELECTPAGE);
	bitsong1.LoadBitmap(IDB_BGOVERWATCH);
	bitsong2.LoadBitmap(IDB_BGVIRUS);
	bitsong3.LoadBitmap(IDB_BGEnergetic);
	bitsong4.LoadBitmap(IDB_BGLoveScenario);
	bitsong5.LoadBitmap(IDB_BGLastTribe);
	bitsong6.LoadBitmap(IDB_BGPassa);
	bitsong7.LoadBitmap(IDB_BGDes);
	bitsong8.LoadBitmap(IDB_BGBoom);
	bitsong9.LoadBitmap(IDB_BGWedding);
	bitsong10.LoadBitmap(IDB_BGMental);
	backbtn.LoadBitmap(IDB_BACKBTN);
	backbtn1.LoadBitmap(IDB_ONBACKBTN);
	selectbtn.LoadBitmap(IDB_SELECTBTN);
	selectbtn1.LoadBitmap(IDB_ONSELECTBTN);
	leftbtn.LoadBitmap(IDB_LEFTBTN);
	leftbtn1.LoadBitmap(IDB_ONLEFTBTN);
	rightbtn.LoadBitmap(IDB_RIGHTBTN);
	rightbtn1.LoadBitmap(IDB_ONRIGHTBTN);
	onselected.LoadBitmap(IDB_ONSELECTED);
	easymode.LoadBitmap(IDB_EASYMODE);
	mediummode.LoadBitmap(IDB_MEDIUMMODE);
	hardmode.LoadBitmap(IDB_HARDMODE);
	oneasymode.LoadBitmap(IDB_ONBTNEASY);
	onmediummode.LoadBitmap(IDB_ONBTNNORMAL);
	onhardmode.LoadBitmap(IDB_ONBTNHARD);


	pold = memDC.SelectObject(&bitpage);

	switch (selectpage) {
	case 0:
		//1번째 노래
		memDC1.SelectObject(&bitsong1);
		memDC.TransparentBlt(190, 50, 300, 200, &memDC1, 0, 0, 300, 200, RGB(75, 0, 130));
		//2번째 노래
		memDC1.SelectObject(&bitsong2);
		memDC.TransparentBlt(490, 50, 300, 200, &memDC1, 0, 0, 300, 200, RGB(75, 0, 130));
		//3번째 노래
		memDC1.SelectObject(&bitsong3);
		memDC.TransparentBlt(790, 50, 300, 200, &memDC1, 0, 0, 300, 200, RGB(75, 0, 130));
		//4번째 노래
		memDC1.SelectObject(&bitsong4);
		memDC.TransparentBlt(190, 250, 300, 200, &memDC1, 0, 0, 300, 200, RGB(75, 0, 130));
		//5번째 노래
		memDC1.SelectObject(&bitsong5);
		memDC.TransparentBlt(490, 250, 300, 200, &memDC1, 0, 0, 300, 200, RGB(75, 0, 130));
		//6번째 노래
		memDC1.SelectObject(&bitsong6);
		memDC.TransparentBlt(790, 250, 300, 200, &memDC1, 0, 0, 300, 200, RGB(75, 0, 130));
		//7번째 노래
		memDC1.SelectObject(&bitsong7);
		memDC.TransparentBlt(190, 450, 300, 200, &memDC1, 0, 0, 300, 200, RGB(75, 0, 130));
		//8번째 노래
		memDC1.SelectObject(&bitsong8);
		memDC.TransparentBlt(490, 450, 300, 200, &memDC1, 0, 0, 300, 200, RGB(75, 0, 130));
		//9번째 노래
		memDC1.SelectObject(&bitsong9);
		memDC.TransparentBlt(790, 450, 300, 200, &memDC1, 0, 0, 300, 200, RGB(75, 0, 130));
		break;
	case 1:
		//10번째 노래
		memDC1.SelectObject(&bitsong10);
		memDC.TransparentBlt(190, 50, 300, 200, &memDC1, 0, 0, 300, 200, RGB(75, 0, 130));
	}
		//노래 골랐을때 효과
	if (melody_no != -1 && melody_no < 11) {
		memDC1.SelectObject(&onselected);
		memDC.TransparentBlt(180 + 300 * ((melody_no + 2) % 3), 40 + ((melody_no + 2) / 3 - 1) % 3 * 200, 320, 220, &memDC1, 0, 0, 320, 220, RGB(34, 177, 76));
	}

	//버튼
	if (m_ptMouse.x > 380 && m_ptMouse.x < 630 && m_ptMouse.y > 670 && m_ptMouse.y < 770) {
		memDC1.SelectObject(&backbtn1);
		memDC.TransparentBlt(380, 670, 250, 100, &memDC1, 0, 0, 250, 100, RGB(255, 255, 255));
	}
	else {
		memDC1.SelectObject(&backbtn);
		memDC.TransparentBlt(380, 670, 250, 100, &memDC1, 0, 0, 250, 100, RGB(255, 255, 255));
	}
	if (m_ptMouse.x > 650 && m_ptMouse.x < 900 && m_ptMouse.y > 670 && m_ptMouse.y < 770) {
		memDC1.SelectObject(&selectbtn1);
		memDC.TransparentBlt(650, 670, 250, 100, &memDC1, 0, 0, 250, 100, RGB(255, 255, 255));
	}
	else {
		memDC1.SelectObject(&selectbtn);
		memDC.TransparentBlt(650, 670, 250, 100, &memDC1, 0, 0, 250, 100, RGB(255, 255, 255));
	}

	if (m_ptMouse.x > 0 && m_ptMouse.x < 210 && m_ptMouse.y > 275 && m_ptMouse.y < 485) {
		memDC1.SelectObject(&leftbtn1);
		memDC.TransparentBlt(0, 275, 210, 210, &memDC1, 20, 20, 230, 230, RGB(34, 177, 76));
	}
	else {
		memDC1.SelectObject(&leftbtn);
		memDC.TransparentBlt(0, 275, 210, 210, &memDC1, 20, 20, 230, 230, RGB(34, 177, 76));
	}
	if (m_ptMouse.x > 1090 && m_ptMouse.x < 1280 && m_ptMouse.y > 275 && m_ptMouse.y < 485) {
		memDC1.SelectObject(&rightbtn1);
		memDC.TransparentBlt(1090, 275, 210, 210, &memDC1, 20, 20, 230, 230, RGB(34, 177, 76));
	}
	else {
		memDC1.SelectObject(&rightbtn);
		memDC.TransparentBlt(1090, 275, 210, 210, &memDC1, 20, 20, 230, 230, RGB(34, 177, 76));
	}
	
	//모드선택 버튼
	switch (mode) {
	case 0:
		memDC1.SelectObject(&oneasymode);
		memDC.TransparentBlt(10, 670, 100, 100, &memDC1, 0, 0, 140, 140, RGB(0, 0, 0));

		memDC1.SelectObject(&mediummode);
		memDC.TransparentBlt(110, 670, 100, 100, &memDC1, 0, 0, 145, 141, RGB(0, 0, 0));

		memDC1.SelectObject(&hardmode);
		memDC.TransparentBlt(210, 670, 100, 100, &memDC1, 0, 0, 145, 141, RGB(0, 0, 0));
		break;
	case 1:
		memDC1.SelectObject(&easymode);
		memDC.TransparentBlt(10, 670, 100, 100, &memDC1, 0, 0, 140, 140, RGB(0, 0, 0));

		memDC1.SelectObject(&onmediummode);
		memDC.TransparentBlt(110, 670, 100, 100, &memDC1, 0, 0, 145, 141, RGB(0, 0, 0));

		memDC1.SelectObject(&hardmode);
		memDC.TransparentBlt(210, 670, 100, 100, &memDC1, 0, 0, 145, 141, RGB(0, 0, 0));
		break;
	case 2:
		memDC1.SelectObject(&easymode);
		memDC.TransparentBlt(10, 670, 100, 100, &memDC1, 0, 0, 140, 140, RGB(0, 0, 0));

		memDC1.SelectObject(&mediummode);
		memDC.TransparentBlt(110, 670, 100, 100, &memDC1, 0, 0, 145, 141, RGB(0, 0, 0));

		memDC1.SelectObject(&onhardmode);
		memDC.TransparentBlt(210, 670, 100, 100, &memDC1, 0, 0, 145, 141, RGB(0, 0, 0));
		break;
	}
	

	dc.BitBlt(0, 0, 1280, 800, &memDC, 0, 0, SRCCOPY);
	Invalidate(false);
	memDC.SelectObject(pold);
}


void Crythm01View::RankPage()
{
	CClientDC dc(this);

	CDC memDC, memDC1;
	CBitmap rankback, rankS, rankA, rankB, rankC, Homebutton, Homebutton1, *pold;

	memDC.CreateCompatibleDC(&dc);
	memDC1.CreateCompatibleDC(&dc);

	rankback.LoadBitmap(IDB_RANK_BACK);
	rankS.LoadBitmap(IDB_RANKS);
	rankA.LoadBitmap(IDB_RANKA);
	rankB.LoadBitmap(IDB_RANKB);
	rankC.LoadBitmap(IDB_RANKC);
	Homebutton.LoadBitmap(IDB_BACKBTN);
	Homebutton1.LoadBitmap(IDB_ONBACKBTN);
	pold = memDC.SelectObject(&rankback);

	memDC1.SelectObject(&rankback);
	memDC.BitBlt(0, 0, 1280, 800, &memDC1, 0, 0, SRCCOPY);

	if (m_ptMouse.x > 500 && m_ptMouse.x < 750 && m_ptMouse.y > 650 && m_ptMouse.y < 750) {
		memDC1.SelectObject(&Homebutton1);
		memDC.TransparentBlt(500, 650, 250, 100, &memDC1, 0, 0, 250, 100, RGB(255, 255, 255));
	}
	else {
		memDC1.SelectObject(&Homebutton);
		memDC.TransparentBlt(500, 650, 250, 100, &memDC1, 0, 0, 250, 100, RGB(255, 255, 255));
	}

	switch (power) {
	case 3:
		memDC1.SelectObject(&rankS);
		memDC.TransparentBlt(800, 200, 375, 465, &memDC1, 0, 0, 375, 465, RGB(0, 0, 0));
		break;
	case 2:
		memDC1.SelectObject(&rankA);
		memDC.TransparentBlt(800, 200, 375, 465, &memDC1, 0, 0, 375, 465, RGB(0, 0, 0));
		break;
	case 1:
		memDC1.SelectObject(&rankB);
		memDC.TransparentBlt(800, 200, 375, 465, &memDC1, 0, 0, 375, 465, RGB(0, 0, 0));
		break;
	case 0:
		memDC1.SelectObject(&rankC);
		memDC.TransparentBlt(800, 200, 375, 465, &memDC1, 0, 0, 375, 465, RGB(0, 0, 0));
		break;
	}

	dc.BitBlt(0, 0, 1280, 800, &memDC, 0, 0, SRCCOPY);
	Invalidate(false);

	memDC.SelectObject(pold);
}
