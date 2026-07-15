#include <iomanip>
#include <iostream>
#include <limits>

#include "generator/DummyDataGenerator.h"
#include "repository/SampleRepository.h"

using dummygen::generator::DummyDataGenerator;
using dummygen::repository::SampleRepository;

int main() {
    SampleRepository repo("data/samples.json");

    std::cout << "==================================================\n";
    std::cout << " Dummy 데이터 생성 Tool (Sample -> data/samples.json)\n";
    std::cout << "==================================================\n";
    std::cout << "생성할 시료 더미 데이터 개수 > ";

    int count = 0;
    if (!(std::cin >> count) || count <= 0) {
        std::cout << "1 이상의 정수를 입력해야 합니다.\n";
        return 1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    DummyDataGenerator generator(repo);
    auto created = generator.generate(count);

    std::cout << "\n총 " << created.size() << "건 생성 완료 (data/samples.json 에 저장됨)\n\n";
    std::cout << std::left << std::setw(10) << "ID" << std::setw(20) << "시료명"
               << std::setw(16) << "평균생산시간" << std::setw(10) << "수율" << "재고\n";
    for (const auto& s : created) {
        std::cout << std::left << std::setw(10) << s.id << std::setw(20) << s.name
                   << std::setw(16) << s.avgProcessTimeMin << std::setw(10) << s.yieldRate
                   << s.stock << " ea\n";
    }

    return 0;
}
