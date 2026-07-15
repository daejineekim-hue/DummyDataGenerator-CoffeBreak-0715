# CLAUDE.md

이 저장소는 반도체 시료 생산주문관리 시스템 개인과제의 **PoC 4 (Dummy 데이터 생성 Tool)** 입니다.

## 범위

- `Sample` 더미 데이터를 생성해 `data/samples.json`에 저장하는 것이 목적입니다.
- 생성된 데이터는 반드시 `SampleRepository.create()`를 통해 저장하여, 기존
  데이터를 덮어쓰지 않고 이어서 채번합니다.
- JSON/Sample/Repository 코드는 DataPersistence PoC와 동일한 구현을 vendoring
  했습니다 (namespace만 `dummygen::*`로 조정). 스키마 변경 시 세 저장소
  (DataPersistence, DataMonitor, DummyDataGenerator) 모두 함께 갱신해야 합니다.

## 규칙

- 무작위 값은 `std::random_device`로 시드한 `std::mt19937`을 사용합니다.
- ID 중복을 피하기 위해 항상 기존 파일의 최대 번호를 조회한 뒤 다음 번호부터 생성합니다.
