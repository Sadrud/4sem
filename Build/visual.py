import matplotlib.pyplot as plt

def read_coordinates(file_path):
    """Читает координаты из файла с учетом количества исходных точек"""
    with open(file_path, 'r') as file:
        # Читаем первую строку - количество исходных точек
        first_line = file.readline().strip()
        try:
            num_original_points = int(first_line)
        except ValueError:
            print(f"Ошибка: первая строка должна содержать число. Получено: '{first_line}'")
            return [], []
        
        original_x = []
        original_y = []
        additional_x = []
        additional_y = []
        
        for i, line in enumerate(file):
            line = line.strip()
            if not line:
                continue
            try:
                x, y = map(float, line.split(' '))
                if i < num_original_points:
                    original_x.append(x)
                    original_y.append(y)
                else:
                    additional_x.append(x)
                    additional_y.append(y)
            except ValueError as e:
                print(f"Ошибка в строке {i+2}: '{line}'. Пропускаю...")
    
    return original_x, original_y, additional_x, additional_y

def save_polygon_image(orig_x, orig_y, add_x, add_y, output_file='polygon.png'):
    """Сохраняет изображение с исходными точками и построенным многоугольником"""
    if not orig_x and not add_x:
        print("Ошибка: нет данных для отрисовки!")
        return
    
    plt.figure(figsize=(10, 8))
    
    # Рисуем исходные точки (красные кружки)
    if orig_x:
        plt.plot(orig_x, orig_y, 'ro', markersize=3, label='Исходные точки')
    
    # Рисуем дополнительные точки и соединяем их (синие линии)
    if add_x:
        # Замыкаем многоугольник, если точек достаточно
        if len(add_x) > 2:
            closed_x = add_x + [add_x[0]]
            closed_y = add_y + [add_y[0]]
            plt.plot(closed_x, closed_y, 'b-', linewidth=2, label='Построенный многоугольник')
        plt.plot(add_x, add_y, 'bo', markersize=5, label='Дополнительные точки')
    
    plt.xlabel('X координата')
    plt.ylabel('Y координата')
    plt.title('Исходные точки и построенный многоугольник')
    plt.grid(True)
    #plt.legend()
    
    # Сохраняем изображение
    plt.savefig(output_file, dpi=300, bbox_inches='tight')
    plt.close()
    print(f"Изображение сохранено в файл: {output_file}")

if __name__ == "__main__":
    input_file = 'input/first.txt'    # Файл с координатами
    output_file = 'polygon.png'  # Название выходного файла

    orig_x, orig_y, add_x, add_y = read_coordinates(input_file)
    save_polygon_image(orig_x, orig_y, add_x, add_y, output_file)
