# DummyDataGenerator-CoffeBreak-0715

반도체 시료 생산주문관리 시스템의 **PoC 4: Dummy 데이터 생성 Tool**.

테스트용 `Sample`(시료) 더미 데이터를 무작위로 생성하여, `DataPersistence` /
`DataMonitor` PoC와 동일한 포맷의 `data/samples.json`에 바로 추가합니다.

## 구조

```
include/json/JsonValue.h        # 동일한 JSON 파서/직렬화기 (namespace만 dummygen::json)
include/model/Sample.h          # Sample 엔티티 + JSON 변환
include/repository/SampleRepository.h  # 파일 기반 CRUD 저장소 (DataPersistence PoC와 동일)
include/generator/DummyDataGenerator.h # 무작위 Sample 생성 로직
src/main.cpp                    # 개수 입력 -> 생성 -> data/samples.json 에 저장
```

## 생성 규칙

- 시료 ID: 기존 `data/samples.json`에서 `S-###` 패턴의 최대 번호를 찾아 그 다음 번호부터 채번 (중복 방지)
- 시료명: 미리 정의된 6종의 시료명 중 무작위 선택
- 평균 생산시간: 0.1 ~ 1.0 min 사이 무작위 (소수 둘째 자리 반올림)
- 수율: 0.70 ~ 0.99 사이 무작위 (소수 둘째 자리 반올림)
- 재고: 0 ~ 1000 사이 무작위 정수

## 빌드 및 실행

```powershell
./build.ps1
./build/dummy_data_generator.exe
```

실행 후 생성할 개수를 입력하면 즉시 `data/samples.json`에 반영되고, 생성된
목록이 콘솔에 출력됩니다. `DataMonitor` PoC를 함께 실행해두면 생성 직후
모니터링 화면에 반영되는 것을 확인할 수 있습니다.
