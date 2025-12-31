# Heaven's Fortress

**Heaven's Fortress** は、様々なミニゲーム（チェス、戦車戦、レース、シューティング）を楽しめるオンラインマルチプレイヤーゲームです。

## 必要要件

- **OS**: Windows 10/11, macOS, Linux
- **ライブラリ**: SDL2, SDL2_mixer, GLEW, OpenGL (freeglut)

## インストール方法

### Windows
1. [Releases](https://github.com/Teru0822/Heaven-sFortress/releases)ページから最新のインストーラー（`HeavensFortress-*-win64.zip` または `.exe`）をダウンロードします。
2. ZIPファイルを解凍するか、インストーラーを実行してインストールしてください。

### Linux
1. [Releases](https://github.com/Teru0822/Heaven-sFortress/releases)ページから最新のソースアーカイブ（`HeavensFortress-*-source.tar.gz`）をダウンロードします。
2. 以下の手順でビルドしてください。

#### Linux ビルド手順

**必要なパッケージのインストール (Ubuntu/Debian):**
```bash
sudo apt-get update
sudo apt-get install build-essential cmake libsdl2-dev libsdl2-mixer-dev \
                     libglew-dev freeglut3-dev libomp-dev libgl1-mesa-dev \
                     libglu1-mesa-dev mesa-common-dev pkg-config
```

**ビルド:**
```bash
# ソースアーカイブを解凍
tar xzf HeavensFortress-*-source.tar.gz
cd HeavensFortress-source

# ビルドディレクトリを作成
mkdir build && cd build

# CMakeで設定
cmake .. -DCMAKE_BUILD_TYPE=Release

# ビルド (並列ビルドで高速化)
make -j$(nproc)

# オプション: システムにインストール
sudo make install

# または、DEBパッケージを作成
cpack -G DEB
```

ビルド後、実行ファイルは `build` ディレクトリ内に生成されます：
- `HeavensFortressClient` (ゲームクライアント)
- `HeavensFortressServer` (ゲームサーバー)

## 実行方法

このゲームはクライアント・サーバー方式で動作します。遊ぶにはサーバーを立ち上げ、そこにプレイヤー（クライアント）が接続する必要があります。

### ネットワーク設定の確認

#### サーバーの IP アドレスを調べる

**Windows:**
```cmd
ipconfig
```
「IPv4 アドレス」の項目を確認してください（例: `192.168.1.10`）

**Linux/macOS:**
```bash
ip addr show
# または
ifconfig
```
`inet` の項目を確認してください（例: `192.168.1.10`）

#### ポート番号について

- **ポート番号**: サーバー起動時に指定する任意の番号（例: `50100`, `10000` など）
- **推奨範囲**: `10000` ～ `65535` の範囲で、他のアプリケーションと重複しない番号を選んでください
- **ファイアウォール**: 選んだポート番号をファイアウォールで許可する必要がある場合があります

**Windows ファイアウォールの設定例:**
1. 「Windows Defender ファイアウォール」を開く
2. 「詳細設定」→「受信の規則」→「新しい規則」
3. 「ポート」を選択し、使用するポート番号（例: `50100`）を入力
4. 「接続を許可する」を選択

**Linux ファイアウォール (ufw) の設定例:**
```bash
sudo ufw allow 50100/tcp
sudo ufw allow 50100/udp
```

### 1. サーバーの起動
コマンドライン（またはターミナル）からサーバープログラムを実行します。

```bash
# Windows
HeavensFortressServer.exe [クライアント数] [ポート番号]

# Linux
./HeavensFortressServer [クライアント数] [ポート番号]

# 例: 2人で遊ぶ場合、ポート50100を使用
HeavensFortressServer 2 50100
```
※ ポート番号を省略した場合、デフォルトポートが使用されます。

サーバーが起動したら、表示される IP アドレスとポート番号をメモしてください。

### 2. クライアントの接続
各プレイヤーはクライアントプログラムを実行し、サーバーに接続します。

```bash
# Windows
HeavensFortressClient.exe [サーバーIP] [ポート番号]

# Linux
./HeavensFortressClient [サーバーIP] [ポート番号]

# 例1: 自分のPCでサーバーも動かしている場合 (ローカル接続)
HeavensFortressClient 127.0.0.1 50100

# 例2: 同じネットワーク内の別のPC (IP: 192.168.1.10) のサーバーに接続する場合
HeavensFortressClient 192.168.1.10 50100

# 例3: インターネット越しに接続する場合 (サーバーのグローバルIP)
HeavensFortressClient 203.0.113.10 50100
```

**接続のヒント:**
- **ローカル接続** (`127.0.0.1`): 同じPC上でサーバーとクライアントを動かす場合
- **LAN接続** (例: `192.168.x.x`): 同じWi-Fiやネットワーク内の別のPCに接続する場合
- **インターネット接続**: サーバー側でポートフォワーディング（ポート開放）が必要です

起動後、プレイヤー名を入力してゲームに参加します。

## ゲームモード (Scenes)

ゲーム内には「広場」と呼ばれるロビーがあり、そこから各ゲームモードへ移動できます。

1.  **Portal (広場)**: ロビーエリア。他のプレイヤーとチャットしたり、各ゲームへのポータルに入ることができます。
2.  **Chess (チェス)**: 戦略ボードゲーム。2人のプレイヤーで対戦します。
3.  **Tank (戦車戦)**: 戦車に乗って砲撃戦を行います。
4.  **Race (レース)**: スポーツカーでコースを競走します。
5.  **Shooting (シューティング)**: 銃を使ったFPS/TPS視点の戦闘です。

## 操作方法

基本操作はキーボードとマウスを使用します。

### 共通操作
- **移動**: W, A, S, D
- **ジャンプ**: Space
- **視点移動**: マウス移動
- **メニュー/終了**: Esc

### 各モード特有の操作
- **戦車 (Tank)**:
  - **発射**: 左クリック
  - **砲塔旋回**: マウス移動
- **レース (Race)**:
  - **加速/減速**: W / S
  - **ハンドル**: A / D
  - **車種変更**: 数字キー '1', '2' (待機中のみ)
- **シューティング (Shooting)**:
  - **発砲**: 左クリック
  - **エイム (照準)**: 右クリック (ホールドまたはトグル)
- **チェス (Chess)**:
  - **駒の選択/配置**: マウス操作
  - **視点変更**: マウスドラッグ

## 開発者向け情報

### ビルド環境
- **CMake** 3.10 以上
- **C++17** 対応コンパイラ
- **依存ライブラリ**: SDL2, SDL2_mixer, GLEW, OpenGL, freeglut, OpenMP

### Windows でのビルド
```bash
# vcpkg で依存関係をインストール
vcpkg install sdl2 sdl2-mixer glew freeglut opengl --triplet x64-windows

# ビルド
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkgのパス]/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release
```

### Linux でのビルド
上記「Linux ビルド手順」を参照してください。
