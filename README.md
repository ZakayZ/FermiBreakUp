# Fermi Break Up

## Описание

Обособленный модуль для расчета распада Ферми аналогичный G4FermiBreakUp из https://github.com/Geant4/geant4.
Отличается тем, что не зависит от классов G4, имеет настройку используемых табличных данных, чем упрощает сборку проекта. А также лечит [некорректное поведение](https://geant4-forum.web.cern.ch/t/strange-results-of-g4fermibreakup-in-v10-4/3137) в версиях старше 10.

## Зависимости

**CLHEP** >= 2.0

## Установка

В корне выполняем:

- Создаем папку для артефактов сборки.

```shell
mdkir build && cd build
```

- Собираем библиотеку.

```shell
cmake -DCMAKE_BUILD_TYPE=Release .. [-DCMAKE_PREFIX_PATH=/path/to/clhep_install]
cmake --build . -j $(nproc)
```

- Устанавливаем библиотеку `FermiBreakUp`

Установка по умолчанию

```shell
sudo cmake --install .
```

Или устанавливаем в определенную директорию.

```shell
cmake --install . --prefix path/to/install
```

## Настройка

На данный момент есть возможность передать свою таблицу масс ядер, однако если значения в ней противоречивы, то возможны исключения во время работы.
Для этого существует два способа:

- Через `.csv` файл, в котором присутствуют 3 обязательных поля: Атомное число, Зарядовое число и масса ядра в `MeV`([пример](tests/data/small_nuclei_data.csb)). Названия для данных полей могут быть переданы как аргументы в соответствующий билдер таблицы `CSVBuilder`.
- С помозью своего билдера, который наследует `fbu::VFermiPropertiesBuilder`, который заполняет таблицу в методе `Build`. `fbu::NucleiProperties props(<Your builder here>);`

Аналогично можно реализовать заполнение таблицы с возможными фрагментами распада `fbu::fragment_pool`.
