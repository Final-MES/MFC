
# HIM MES - Smart Factory Monitoring System

![Language](https://img.shields.io/badge/language-C%2B%2B-blue)
![Framework](https://img.shields.io/badge/framework-MFC-informational)
![Platform](https://img.shields.io/badge/platform-Windows-lightgrey)

## 📌 프로젝트 개요

**HIM MES**(Manufacturing Execution System)는 스마트팩토리 환경에서 생산, 설비, 시스템 상태를 직관적으로 시각화하고 관리할 수 있도록 설계된 Windows 기반 MFC 애플리케이션입니다.

- ✔️ 생산 계획 및 실시간 상태 모니터링
- ✔️ 설비 가동 현황 및 예방정비 관리
- ✔️ 사용자 및 시스템 설정, 로그 관리
- ✔️ 직관적인 대시보드 & 위젯 기반 UI
- ✔️ 깜빡임 애니메이션 및 아이콘 시각화

## 🧱 주요 구성

### 🖥 로그인 화면 (`LoginDlg`)
- 사용자 인증
- 우측 일러스트 삽입 (`IDC_STATIC_RIGHT_IMAGE`)
- 사용자 친화적 폰트 & 색상

### 🏠 메인 화면 (`MainDlg`)
- 네비게이션 메뉴: 대시보드 / 생산 / 설비 / 시스템
- 상태바: 사용자, 버전, 최종 접속 시간 표시
- Owner-draw 버튼 2x2 레이아웃 적용

### 📊 대시보드 (`DashboardDlg`)
- KPI, 실시간 현황, 경고 등 요약 제공  
(*파일 구조에 정의됨 - 현재 UI 구현 생략 또는 예정*)

### 🏭 생산관리 (`ProductionDlg`)
- **생산 계획 수립**: 월간 계획표, 달력 기반 인터페이스
- **작업 지시 및 일정**: 간트 차트 스타일의 작업 바
- **실시간 생산 상황** 및 **생산 실적 추적** 위젯
- 애니메이션 효과, 버튼 강조 상태 구현

### 🛠 설비관리 (`EquipDlg`)
- 설비 가동 현황
- 예방 정비 계획
- 성능 모니터링
- 고장 및 정비 이력

### ⚙ 시스템 구성 (`SystemDlg`)
- 사용자 권한 관리
- 시스템 환경 설정
- 로그 및 감사 추적
- 데이터 백업 및 복원
- 위젯 기반 직관적 설정 UI

## 🎨 기술 스택

| 항목         | 내용                             |
|--------------|----------------------------------|
| 언어         | C++                              |
| 프레임워크   | MFC (Microsoft Foundation Class) |
| 플랫폼       | Windows (Desktop)                |
| 개발 툴      | Visual Studio                    |
| UI 구성       | Owner-Draw 버튼 + Custom Paint  |

## 📁 파일 구조 요약

```bash
├── MainDlg.cpp/h           # 메인 메뉴
├── LoginDlg.cpp/h          # 로그인 화면
├── DashboardDlg.cpp/h      # 대시보드
├── ProductionDlg.cpp/h     # 생산관리
├── EquipDlg.cpp/h          # 설비관리
├── SystemDlg.cpp/h         # 시스템 구성
├── HIM_MESDlg.cpp/h        # 앱 초기 구동
├── resource.h              # 리소스 매핑
```

## 🛠 빌드 및 실행

1. Visual Studio에서 `.sln` 프로젝트 열기
2. `Debug` 또는 `Release` 모드로 설정
3. 빌드 후 실행 (F5)

## 📸 스크린샷 (선택사항)

> 추후 주요 화면 캡처 삽입 가능

---

## 🙌 제작자 및 기여

이 프로젝트는 스마트팩토리 MES 시각화 및 관리 시스템 구현을 목표로 개발되었습니다.  
기여 및 개선 사항은 PR 또는 이슈로 남겨주세요!
