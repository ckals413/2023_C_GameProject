# 🎮C  - GameProject 🎮
### 👾게임요약👾
![ezgif com-video-to-gif-converter (2)](https://github.com/ckals413/2023_C_GameProject/assets/124526270/c0b0142a-a360-467c-9ed1-81be615d398b)

![2-ezgif com-video-to-gif-converter](https://github.com/ckals413/2023_C_GameProject/assets/124526270/a2ecddcf-c581-4a23-87da-67bd5e434636)

![ezgif com-video-to-gif-converter (3)](https://github.com/ckals413/2023_C_GameProject/assets/124526270/4657dbe6-226e-4685-99bf-72b730207809)

---
<details>
    <summary>📣작품개요📣</summary>
    <p>
 우주에서 생성되는 몬스터 로부터 떨어지는 폭탄을 피해 생존해, 몬스터를 처치하고, 여러 스테이지를 거쳐 최종 빅 몬스터를 처치해 우주를 지키는 게임입니다. 시간에 따라 랜덤으로 7개의 아이템들이 생성되어 아래로 떨어지며 아이템 획득 시 새로운 능력을 얻게 됩니다. 만약 플레이어의 시간 또는 생명이 없다면 코인을 주입하면, 시간이나 생명이 추가됩니다. 자세한 설명은 아래와 같습니다.  
 <br>

 **실행화면 크기**: 90x55 
</p>
</details>

---
<details>
    <summary>👾게임 설명👾</summary>


### 초기화면
- (1) 게임 시작, 게임 설명, 게임 종료
- (2) 배경음악 재생
- (3) 시간에 따라 깜빡거리 듯 색상 변경

### 게임 실행
- (4) 위에서 몬스터가 좌우로 움직이고 폭탄을 낙하
- (5) 플레이어 좌, 우, 앞, 뒤로 움직임(방향키 사용)
- (6) 플레이어 총알발사 (space 사용), 궁극기 발사(‘d’ 사용)
- (7) 코인주입(‘h’ 사용)
- (8) 플레이어 목숨4개
- (9) 플레이어 아이템 7개 랜덤 생성
  - 플레이어 옆으로 1개 복제(갤러그처럼)
  - 이동속도 제어(몬스터, 플레이어)
  - 적 총알 전멸
  - 궁극기
  - 시간 추가
  - 생명 추가
- (10) 남은 시간표시
- (11) 코인 넣으면 생명추가
- (12) 몬스터 처치 점수 카운트
- (13) 시간에 따른 몬스터 이동속도 변화
- (14) stage 생성(EX)
  - stage1: 총알 수직으로 떨어짐(시간이 30초 이하 남으면 몬스터2 생성)
  - stage2: 총알이 플레이어를 따라옴(시간이 40초 이하 남으면 미니몬스터 생성: 플레이어를 따라다님)
  - stage 3: 보스 전(미니 몬스터가 플레이어를 따라다님)
- (15) 효과음 넣기(총알, 궁극기 발사 시/적 몬스터 처치 시)

### 엔딩
- (16) 죽으면 "LOOSE" (배경음악 삽입)
- (17) 마지막 보스까지 깨면 "WIN"(배경음악 삽입)
- (18) 점수 판 넣어서 순위 작성
- (19) 다시 실행하기/종료(‘R’,’Q’)

### 실행 화면
- 필요한 경우 추가 설명을 포함할 수 있습니다.
- 아이템 설명
  - C: 플레이어 복제(갤러그), 생명 감소 시 리셋, 보스 체력감소 -5
  - H: 목숨 +1
  - B: 적들의 총알 전멸
  - Q: 궁극기, 보스 체력감소 -10
  - S: 플레이어 이동속도 및 스피드증가
  - S: 적 이동속도 및 스피드 감소
  - T: 시간을 10초 추가

### 스테이지 상세

#### STAGE 1
- 적 1은 좌우로 움직이면서 수직으로 총알을 발사합니다.
- 남은 시간이 30초가 되면 적 2가 출몰하고 이동속도와 총알의 속도가 빠르고 총알을 수직 발사하며, 일정 시간이 지나면 아이템들이 출몰합니다.
- 10초마다 적의 총알 속도가 빨라집니다.

#### STAGE 2
- 적 1은 좌우로 움직이고 플레이어의 x축 방향으로 따라다니며 총알을 수직 발사합니다.
- 적 2는 좌우로 움직이고 이동속도와 총알의 속도가 빠르며 총알을 수직 발사합니다.
- 미니 몬스터는 남은 시간이 40초가 되면 출몰하고 느린 속도로 플레이어를 쫓아다닙니다. 플레이어가 미니 몬스터와 충돌하면 생명이 1 감소합니다.
- 일정 시간이 지나면 아이템들이 출몰하며, 10초마다 적의 총알 속도가 빨라집니다.

#### STAGE BOSS
- 적 2는 좌우로 움직이고 이동속도와 총알의 속도가 빠르며 총알을 수직 발사합니다.
- 미니 몬스터는 느린 속도로 플레이어를 쫓아다닙니다.
- 빅 몬스터는 가로로 긴 총알을 수직으로 발사하고 플레이어를 좌우로 따라다닙니다.
- 15초마다 빅 몬스터의 이동속도 및 총알 속도가 증가합니다.
- 보스 스테이지에서 플레이어 복제 아이템과 궁극기 아이템은 빅 몬스터의 체력을 각
<br><br>

</details>

--- 

<details>
    <summary>🎲게임실행 과정🎲</summary>



![image](https://github.com/ckals413/2023_C_GameProject/assets/124526270/160fa4f5-e5b3-4eaf-b0cd-4079e4c91055)

![image](https://github.com/ckals413/2023_C_GameProject/assets/124526270/91853f67-00b7-46e7-8ff3-b84f80d8d6f5)

![image](https://github.com/ckals413/2023_C_GameProject/assets/124526270/27263ce8-1f11-4dc0-a7aa-6ac317695cc0)

![image](https://github.com/ckals413/2023_C_GameProject/assets/124526270/2e3c5aa0-e7ba-4595-8b5c-94a4e111ad59)

![image](https://github.com/ckals413/2023_C_GameProject/assets/124526270/a10dbcf3-cbb8-47c2-b122-0496c379403d)

![image](https://github.com/ckals413/2023_C_GameProject/assets/124526270/de4ac518-8ac1-4d6f-8fd5-6c538c5bc6c0)

![image](https://github.com/ckals413/2023_C_GameProject/assets/124526270/2c1ab964-ee21-4aaf-9fb3-d6f2be9bff67)

![image](https://github.com/ckals413/2023_C_GameProject/assets/124526270/f5b04d21-f8a3-437e-8859-aafc65f8c535)

![image](https://github.com/ckals413/2023_C_GameProject/assets/124526270/2181e326-b57b-4572-a1f4-2e238b72984c)

![image](https://github.com/ckals413/2023_C_GameProject/assets/124526270/9e677a71-4cd1-4a70-8d75-2080a82cefed)

</details>

---

<details>
    <summary>🎞실행영상🎞</summary>

## 게임요약 설명영상
[![Video Label](https://github.com/ckals413/2023_C_GameProject/assets/124526270/4f89c76f-942d-448f-929e-a869dfbb63f1)](https://youtu.be/bfcG2QWJGuE)

## 게임실행 원본영상
[![Video Label](https://github.com/ckals413/2023_C_GameProject/assets/124526270/13be8f3c-e1dd-4908-b203-be93045cf786)](https://youtu.be/94VuX9fxzIo?si=zR9os21u9CGZCu29)
</details>
