# C++ Ray Tracing

레이 트레이싱의 원리를 학습하고, 챕터별로 기능을 확장해 나가는
C++ 렌더링 프로젝트입니다.

현재는 **Chapter 1 — Ray Tracing in One Weekend**를 구현했으며,
이후 챕터를 진행하면서 새로운 기능과 렌더링 결과를 추가할 예정입니다.

## Chapter 1 — 기본 레이 트레이서

카메라에서 픽셀별 광선을 생성하고, 물체와의 충돌 및
재질에 따른 빛의 산란을 계산하여 이미지를 렌더링합니다.

### 주요 기능

- 광선과 구의 교차 계산
- 표면 법선 및 앞면·뒷면 판별
- 여러 물체 중 가장 가까운 충돌 선택
- 다중 샘플링을 통한 안티앨리어싱
- 확산 재질, 금속 반사, 유리 굴절 및 전반사
- 카메라 위치와 시야각 조정
- 피사계 심도 표현
- PPM 이미지 출력

### 기본 구성

| 구성 요소 | 역할 |
| --- | --- |
| Vector3 / Ray | 벡터 연산 및 광선 표현 |
| Hittable / Sphere / HittableList | 물체와 장면의 충돌 처리 |
| HitRecord / Interval | 충돌 정보 및 검사 구간 관리 |
| Material / Lambertian / Metal / Dielectric | 재질별 산란 처리 |
| Camera | 광선 생성, 샘플링 및 이미지 출력 |

## 개발 환경

- C++
- Windows / Visual Studio 2022
- 출력 형식: PPM

## 학습 기록

챕터별 구현 내용을 커밋으로 기록하며,
기능이 추가됨에 따라 README를 업데이트합니다.

## 참고 자료

- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
- [얌얌코딩 — Ray Tracing 학습 자료](https://www.yamyamcoding.com/2e30b1ff-a61e-801f-b1a9-ea972134da03)

본 프로젝트는 위 자료를 참고한 학습용 구현입니다.
