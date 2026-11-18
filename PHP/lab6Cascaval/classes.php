<?php
declare(strict_types=1);

/**
 * Класс, описывающий одну карточку (модель данных).
 */
class Item {
    public function __construct(
        private string $id,
        private string $title,
        private string $description,
        private string $category,
        private string $status,
        private string $targetDate,
        private float $price,
        private string $createdAt = ''
    ) {
        if ($this->createdAt === '') {
            $this->createdAt = date('Y-m-d H:i:s');
        }
    }

    public function getId(): string { return $this->id; }
    public function getTitle(): string { return $this->title; }
    public function getDescription(): string { return $this->description; }
    public function getCategory(): string { return $this->category; }
    public function getStatus(): string { return $this->status; }
    public function getTargetDate(): string { return $this->targetDate; }
    public function getPrice(): float { return $this->price; }
    public function getCreatedAt(): string { return $this->createdAt; }

    /**
     * Конвертирует объект в массив для сохранения в JSON.
     */
    public function toArray(): array {
        return [
            'id' => $this->id,
            'title' => $this->title,
            'description' => $this->description,
            'category' => $this->category,
            'status' => $this->status,
            'target_date' => $this->targetDate,
            'price' => $this->price,
            'created_at' => $this->createdAt
        ];
    }

    /**
     * Создает объект из массива данных.
     */
    public static function fromArray(array $data): self {
        return new self(
            $data['id'] ?? uniqid(),
            $data['title'] ?? '',
            $data['description'] ?? '',
            $data['category'] ?? '',
            $data['status'] ?? 'Нет',
            $data['target_date'] ?? date('Y-m-d'),
            floatval($data['price'] ?? 0),
            $data['created_at'] ?? date('Y-m-d H:i:s')
        );
    }
}

/**
 * Класс для валидации данных формы.
 */
class ItemValidator {
    public function validate(array $data): array {
        $errors = [];
        if (empty($data['title']) || mb_strlen(trim($data['title'])) < 3) {
            $errors[] = "Название должно содержать минимум 3 символа.";
        }
        if (empty($data['description']) || mb_strlen(trim($data['description'])) < 5) {
            $errors[] = "Описание должно содержать минимум 5 символов.";
        }
        if (empty($data['target_date']) || !strtotime($data['target_date'])) {
            $errors[] = "Указана некорректная дата.";
        }
        if (!isset($data['price']) || floatval($data['price']) < 0) {
            $errors[] = "Цена не может быть отрицательной.";
        }
        return $errors;
    }
}

/**
 * Репозиторий для управления хранением карточек в JSON-файле.
 */
class ItemRepository {
    private string $filePath;

    public function __construct(string $filePath) {
        $this->filePath = $filePath;
    }

    /**
     * Возвращает все карточки в виде массива объектов Item.
     * @return Item[]
     */
    public function getAll(): array {
        if (!file_exists($this->filePath)) {
            return [];
        }
        $json = file_get_contents($this->filePath);
        $data = json_decode($json, true);
        if (!is_array($data)) {
            return [];
        }
        return array_map(fn($item) => Item::fromArray($item), $data);
    }

    /**
     * Сохраняет массив объектов в файл.
     * @param Item[] $items
     */
    public function saveAll(array $items): void {
        $data = array_map(fn(Item $item) => $item->toArray(), $items);
        file_put_contents($this->filePath, json_encode(array_values($data), JSON_UNESCAPED_UNICODE | JSON_PRETTY_PRINT));
    }

    public function add(Item $item): void {
        $items = $this->getAll();
        $items[] = $item;
        $this->saveAll($items);
    }

    public function update(Item $updatedItem): void {
        $items = $this->getAll();
        foreach ($items as $index => $item) {
            if ($item->getId() === $updatedItem->getId()) {
                $items[$index] = $updatedItem;
                break;
            }
        }
        $this->saveAll($items);
    }

    public function delete(string $id): void {
        $items = array_filter($this->getAll(), fn(Item $item) => $item->getId() !== $id);
        $this->saveAll($items);
    }

    public function findById(string $id): ?Item {
        foreach ($this->getAll() as $item) {
            if ($item->getId() === $id) {
                return $item;
            }
        }
        return null;
    }
}