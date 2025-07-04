# 🔐 Armários Inteligentes com ESP32 + RFID

Este projeto implementa um sistema de armários inteligentes com controle de acesso via cartões e tags RFID. Cada armário é controlado por uma placa ESP32 e um leitor MFRC522, com dados sincronizados em tempo real usando o Firebase Realtime Database.

## 🚀 Funcionalidades

- Leitura de cartões RFID para reservar ou liberar armários.
- Atualização em tempo real do estado dos armários no Firebase.
- Interface web simples hospedada no Firebase Hosting, mostrando armários abertos ou fechados.
- Controle individual por UID de cartão.

## 🛠 Tecnologias Utilizadas

- ESP32
- Leitor RFID MFRC522
- Firebase Realtime Database
- Firebase Hosting (HTML/CSS/JS)
- Arduino IDE

## 🧾 Estrutura do Firebase

```
/lockers
  ├── locker_01
  │   ├── id: "001"
  │   ├── status: "closed"
  │   ├── uid: "AAAAAAA"
  │   └── lastAccess: "000000"
  └── locker_02
      ├── id: "002"
      ├── status: "open"
      ├── uid: "null"
      └── lastAccess: "000000"
```

## 📁 Organização do Projeto

- `locker_esp/` – Código da ESP32 para controle do armário.
- `web/` – Página web com visualização gráfica do estado dos armários.

⚠️ Atualmente, o repositório contém apenas o código para o `locker_01`. Para adicionar outros armários (como `locker_02`, `locker_03`, etc.), basta duplicar o código e alterar o valor da constante `LOCKER_ID` no arquivo `secrets.h`.

## 🔒 Credenciais

As credenciais (Wi-Fi, Firebase, etc.) estão separadas no arquivo `secrets.h`, que **não está versionado**. Para executar o projeto, crie o seu próprio `secrets.h` com o seguinte conteúdo:

```cpp
#define WIFI_SSID "SUA_REDE_WIFI"
#define WIFI_PASSWORD "SUA_SENHA"
#define API_KEY "SUA_API_KEY"
#define DATABASE_URL "https://seuprojeto.firebaseio.com/"
#define USER_EMAIL "seu@email.com"
#define USER_PASSWORD "suaSenha"
#define LOCKER_ID "locker_01"
```

> ⚠️ Lembre-se de adicionar o arquivo `secrets.h` ao `.gitignore` para não subir dados sensíveis ao GitHub.

## 📄 .gitignore (exemplo)

```
secrets.h
```

## 👨‍💻 Autores

Projeto desenvolvido por João Pedro Ramalho de Sousa, Matheus Bertoldo, Renan Ribeiro Pereira, como parte da disciplina de Internet das Coisas na Universidade Federal de Lavras (UFLA).
