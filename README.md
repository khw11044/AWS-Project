# AWS-Project
1.. AWS IoT Core와 아두이노 (MKR WiFi 1010) 연결하기
1.1 관련 라이브러리 설치
1.	Arduino IDE의 스케치-라이브러리 포함하기-라이브러리 관리 메뉴 클릭
2.	검색 창에서 다음 5가지 라이브러리를 검색하여 설치
o	WiFiNINA (or WiFi101 for the MKR1000)
o	ArduinoBearSSL
o	ArduinoECCX08
o	ArduinoMqttClient
o	Arduino Cloud Provider Examples
1.2 AWS IoT Core에 아두이노 보드를 연결하기 위한 설정
•	AWS IoT Core는 X.509 인증서를 사용하여 디바이스를 인증함.
•	X.509 인증서를 생성하기 위해서, 아두이노 보드에서 CSR(Certificate Signing Request)를 생성한후, 이를 AWS 콘솔에서 업로드할 것이다.
o	CSR 생성 절차
1.	MKR WiFi 1010 보드를 USB 케이블로 컴퓨터와 연결
2.	Arduino IDE의 파일-예제-ArduinoECCX08-Tools-ECCX08CSR 메뉴 선텍
3.	시리얼 모니터 창을 연다. (줄 마침 설정은 Both NL & CR로 되어 있어야 함)
4.	시리얼 모니터 창에서 CSR에 포함될 정보를 입력하는데, 아래 그림과 같이 Common Name 을 제외하곤 모두 빈칸을 입력 (아무 입력없이 전송 버튼을 누름)
	Common Name: MyMKRWiFi1010 입력
 
5.	-----BEGIN CERTIFICATE REQUEST----- 과 -----END CERTIFICATE REQUEST----- 사이에 생성된 CSR 문자열을 복사하여 텍스트 에디터에 붙여넣기 한 후, csr.txt 파일로 저장한다.
	이 파일은 후에 AWS 콘솔에서 X.509 인증서 생성을 위해 업로드 됨
	csr.txt 예시
 
1.3 레지스트리에 디바이스 등록
1.	AWS Management Console에 로그인하고 AWS IoT 콘솔을 엽니다.
2.	왼쪽 탐색 창에서 관리를 선택합니다.
3.	아직 사물이 없습니다 페이지에서 사물 등록을 선택합니다.
 
4.	Creating AWS IoT things(AWS IoT 사물 생성) 페이지에서 Create a single thing(단일 사물 생성)을 선택합니다.
 
5.	사물 생성 페이지의 이름 필드에 MyMKRWiFi1010과 같은 사물의 이름을 입력합니다. 나머지 부분은 그대로 나두고 다음을 선택합니다.
6.	사물에 인증서 추가 페이지에서 CSR을 통한 생성을 선택합니다.
o	앞서 생성한 CSR 파일 (csr.txt)을 선택하고, 열기를 클릭한 후, 파일 업로드를 클릭합니다.
7.	다음 화면에서 사물 등록을 클릭합니다.
8.	이제 여러분은 사물 페이지에서 새롭게 등록된 사물을 확인할 수 있습니다.
 


1.4 AWS IoT 정책 생성
•	X.509 인증서는 AWS IoT에서 디바이스를 인증하는 데 사용합니다.
•	AWS IoT 정책은 디바이스가 MQTT 주제 구독 또는 게시와 같은 AWS IoT 작업을 수행할 수 있는 권한을 부여하는 데 사용합니다.
•	사용자의 디바이스는 AWS IoT(으)로 메시지를 전송할 때 인증서를 제출합니다.
•	디바이스가 AWS IoT 작업을 수행하도록 허용하려면 AWS IoT 정책을 생성하여 디바이스 인증서에 연결해야 합니다.
•	AWS IoT 정책을 생성하려면
1.	왼쪽 탐색 창에서 보안을 선택하고 정책을 선택합니다. [You don't have a policy yet] 페이지에서 [Create a policy]를 선택합니다.
 
2.	정책 생성 페이지의 이름 필드에 정책 이름(예: AllowEverything)을 입력합니다.
	작업 필드에 iot:*를 입력합니다.
	리소스 ARN 필드에 *를 입력합니다.
	[Allow] 확인란을 선택합니다.
	이렇게 하면 모든 클라이언트가 AWS IoT에 연결할 수 있습니다.
 
1.5 디바이스 인증서에 AWS IoT 정책 연결
•	정책을 생성했으면 디바이스 인증서에 이 정책을 연결해야 합니다. 인증서에 AWS IoT 정책을 연결하는 것은 정책에 지정된 권한을 디바이스에 부여하는 것입니다.
1.	왼쪽 탐색 창에서 보안을 선택하고 인증서를 선택합니다.
	인증서가 안보이면 브라우저의 새로고침을 눌러보세요
 
2.	앞서 생성한 인증서의 상자에서 ...를 선택해 드롭다운 메뉴를 연 다음 [정책 연결]를 선택합니다.
 
3.	인증서에 정책 연결 대화 상자에서 앞 단계에서 생성한 정책(AllowEverything) 옆의 확인란을 선택한 다음 연결을 선택합니다.
1.6 디바이스 구성
•	모든 디바이스에는 AWS IoT와 통신할 수 있도록 디바이스 인증서가 설치되어 있어야 합니다.
1.	왼쪽 탐색 창에서 보안을 선택하고 인증서를 선택합니다.
2.	앞서 생성한 인증서의 상자에서 ...를 선택해 드롭다운 메뉴를 연 다음 [다운로드]를 선택합니다.
3.	다운로드된 인증서(xxxxxxxxxx-certificate.perm.crt)를 확인합니다.
4.	왼쪽 탐색 창에서 설정을 선택하고, 엔드포인트를 기억해 둡니다.
5.	Arduino IDE의 파일-예제-Arduino Cloud Provider Examples-AWSIoT-AWS_IoT_WiFi 메뉴 선텍
	arduino_secrets.h 탭에서, 사용가능한 WiFi의 SSID와 Password를 설정
	// Fill in  your WiFi networks SSID and password
	#define SECRET_SSID ""
#define SECRET_PASS ""
	앞에서 확인한 엔드포인트를 SECRET_BROKER 값으로 설정
	// Fill in the hostname of your AWS IoT broker
#define SECRET_BROKER "xxxxxxxxxxxxxx.iot.xx-xxxx-x.amazonaws.com"
	앞에서 다운로드한 인증서 파일을 텍스트 에디터로 열고 값을 복사하여 다음 영역에 붙여넣기 한다.
	// Fill in the boards public certificate
	const char SECRET_CERTIFICATE[] = R"(
	-----BEGIN CERTIFICATE-----
	-----END CERTIFICATE-----
)";
________________________________________
1.7 테스트
1.	스케치 프로그램을 보드에 업로드하고, 시리얼 모니터 창을 연다.
o	보드는 WiFi 네트워크와 연결을 시도하고, 성공하면 AWS IoT에 MQTT를 통해 연결을 시도한다.
 
2.	MQTT Client를 통해 AWS IoT Core와 디바이스 간의 상호작용을 모니터링 한다.
o	디바이스의 스케치 프로그램은 arduino/outgoing 토픽으로 매 5초마다 메시지를 AWS IoT Core로 보내고, arduino/incoming 토픽에 대한 메시지를 기다린다.
o	디바이스에서 AWS IoT로의 상호작용 모니터링
1.	AWS IoT Core 콘솔의 테스트 메뉴를 클릭
2.	구독 주제 (Subscribe topic) 박스에 arduino/outgoing을 입력하고 주제 구독 (Subscribe to topic) 버튼을 클릭한다.
 
	매 5초마다 보드에서 보낸 hello 메시지가 현재 시간정보와 함께 표시된다.  
o	AWS IoT에서 디바이스로의 상호작용 모니터링
1.	주제 게시메뉴의 게시섹션에서, 게시할 주제로 arduino/incoming을 입력하고, 주제 게시 (Publish to topic) 버튼을 클릭한다.
 
2.	시리얼 모니터 창에서 메시지 수신을 확인한다.
 

마지막으로 2개의 디바이스를 등록하고 각각 MKR아두이노에 각각의 코드를 넣어줍니다.
AWS_IoT_WaterLevel 파일의 코드와
AWS_IoT_WaterDoor 파일의 코드를 넣어줍니다. 
각각 인증서를 다르게해주어야합니다.
각각 이름도 다르게 해줍니다. 
예) MyMKRWiFi1010 과 MotorMKR 등

AWS Lambda를 이용한 서버리스 컴퓨팅 시작하기
1. AWS Lambda란?
•	AWS Lambda를 사용하면 서버를 프로비저닝하거나 관리할 필요 없이 코드를 실행할 수 있습니다.
o	코드를 업로드하기만 하면, Lambda에서 높은 가용성으로 코드를 실행 및 확장하는 데 필요한 모든 것을 처리합니다.
o	사용한 컴퓨팅 시간만큼만 비용을 지불하고, 코드가 실행되지 않을 때는 요금이 부과되지 않습니다.
o	다른 AWS 서비스에서 코드를 자동으로 트리거하도록 설정하거나 웹 또는 모바일 앱에서 직접 코드를 호출할 수 있습니다.
•	작동 방식  
•	사용사례
o	실시간 파일 처리
	Amazon S3를 사용하여 업로드하는 즉시 데이터를 처리하도록 AWS Lambda를 트리거할 수 있습니다. 예를 들어, Lambda를 사용하여 실시간으로 이미지를 썸네일하고, 동영상을 트랜스코딩하고, 파일을 인덱싱하고, 로그를 처리하고, 콘텐츠를 검증하고, 데이터를 수집 및 필터링할 수 있습니다.
 
o	IoT 백엔드
	IoT 디바이스에서 생성된 텔레메트리 정보를 DynamoDB 테이블에 채우기 위해서 AWS Lambda를 이용하고, Lambda 함수를 사용하여 데이터베이스에서 특정 장치 일련 번호와 임의로 생성 된 활성화 코드를 검색하여 장치를 활성화하고 장치 소유자의 전자 메일을 동일한 테이블에 등록합니다.
 









1.1 콘솔로 Lambda 함수 만들기
이 시작하기 실습에서는 AWS Lambda 콘솔을 사용하여 Lambda 함수를 생성합니다. 다음으로, 샘플 이벤트 데이터를 사용하여 Lambda 함수를 수동으로 호출합니다. AWS Lambda에서는 Lambda 함수를 실행해 결과를 반환합니다. 그런 다음 Lambda 함수가 생성한 로그와 다양한 CloudWatch 측정치를 포함하여 실행 결과를 확인합니다.
Lambda 함수를 만들려면
1.	AWS Lambda 콘솔을 엽니다.
2.	[Create a function]을 선택합니다.
3.	함수 이름에 my-function을 입력합니다.
4.	함수 생성을 선택합니다.
Lambda는 Node.js 함수와, 함수에 로그를 업로드할 수 있는 권한을 부여하는 실행 역할을 생성합니다. 함수를 실행하면 Lambda가 실행 역할을 수임하고 이를 사용하여 AWS SDK에 대한 자격 증명을 생성하고 이벤트 소스로부터 데이터를 읽습니다.













1.2Eclipse 용 AWS Toolkit 설정
도구 키트 설정
PDF
이 단원에서는 AWS Toolkit for Eclipse를 설치하거나 업그레이드하는 방법을 설명합니다.
사전 요구사항
AWS Toolkit for Eclipse의 사전 요구 사항은 다음과 같습니다.
•	Amazon Web Services 계정 – AWS 계정을 만들려면 AWS 홈 페이지로 이동하여 지금 가입을 클릭합니다. 등록하면 AWS에서 제공하는 모든 서비스를 사용할 수 있습니다.
•	지원되는 운영 체제 – AWS Toolkit for Eclipse는 Windows, Linux, macOS, or Unix에서 지원됩니다.
•	Java 1.8
•	Eclipse IDE for Java Developers 4.2 이상 – Eclipse 다운로드 페이지에서 제공하는 기본 버전으로 현재 AWS Toolkit for Eclipse를 유지합니다.
참고
Eclipse는 다양한 다운로드를 제공합니다. Eclipse IDE for Enterprise Java Developers를 설치하는 것이 좋습니다. 여기에는 Elastic Beanstalk에 필요한 Eclipse Web Tools Platform, Amazon SimpleDB 기능에 필요한 Eclipse Data Tools Platform, Eclipse EGit 및 M2Eclipse가 포함되어 있습니다. 다른 버전의 Eclipse를 설치하는 경우 해당 기능을 지원하는지(또는 제공된 링크를 사용하여 설치했는지) 확인하십시오.
•	(선택 사항) Google ADT(Android Development Tools) – AWS Mobile SDK for Android에 대한 AWS Toolkit for Eclipse 지원이 필요하면 먼저 ADT를 설치해야 합니다.
AWS Toolkit for Eclipse 설치
AWS Toolkit for Eclipse를 설치하려면
1.	Eclipse 내에서 도움말을 클릭한 후 Install New Software(새 소프트웨어 설치)를 클릭합니다.
2.	Work with(작업) 상자에 https://aws.amazon.com/eclipse를 입력한 후 Enter를 누릅니다.
3.	설치하려는 AWS Toolkit for Eclipse의 구성 요소를 선택합니다. 모두 선택을 클릭하여 모든 구성 요소를 한 번에 설치합니다.
참고
•	AWS Core Management Tools 섹션에 있는 AWS Toolkit for Eclipse Core는 필수 사항입니다. 다른 모든 구성 요소는 선택 사항입니다.
•	AWS Mobile SDK for Android 지원이 필요하면 Eclipse용 Google ADT(Android Developer Tools)를 먼저 설치해야 합니다. ADT를 아직 설치하지 않았으면 AWS SDK for Android가 선택되지 않았는지 확인하십시오. 선택되어 있으면 설치에 실패합니다.
•	Amazon RDS 또는 Amazon SimpleDB 관리자 지원이 필요하면 Eclipse Data Tools Platform(DTP)를 설치해야 합니다. DTP는 기본적으로 Eclipse의 "Java EE Developers" 버전과 함께 설치되거나 별도로 설치할 수 있습니다.
4.	선택했으면 다음(또는 완료)를 클릭하여 설치를 완료합니다.
AWS Toolkit for Eclipse를 설정했으면 AWS 자격 증명을 구성해야 합니다.
참고
선택한 옵션 및 요인(네트워크 속도, 서버 지연 시간, 시스템 성능 등)에 따라 설치가 완료되는 데 최대 30분이 걸릴 수 있습니다.
AWS Toolkit for Eclipse 업그레이드
AWS Toolkit for Eclipse를 업그레이드하거나 다시 설치하려면 도구 키트 설치와 동일한 지침을 사용하십시오.
일부 Eclipse 버전(특히 Mars 및 Neon)은 Oomph 플러그인의 이전 버전 버그로 인해 최신 아티팩트를 가져오지 못할 수 있습니다. 이 문제를 해결하려면 다음과 같이 하십시오.
1.	AWS Toolkit for Eclipse 업데이트 사이트로 https://aws.amazon.com/eclipse/site.xml을 사용하고 있는지 확인합니다.
2.	~/.eclipse/org.eclipse.oomph.p2/cache/ 디렉터리를 삭제하여 캐시된 콘텐츠를 삭제합니다.
3.	최신 버전의 Oomph(Eclipse 설치 프로그램)를 설치합니다.

[주의] Eclipse 용 AWS Toolkit은 Java 1.8에서 정상적으로 동작하고, JDK 9 이상에서 실행 시킨 경우에 javax/xml/bind/JAXBException 발생한다. 따라서, Eclipse가 Java 1.8에서 동작하도록 설정을 변경해야 함.
•	eclipse.ini파일을 찾아서, -vm 옵션 다음에 지정하는 JVM 패스를 JDK1.8로 변경함.

1.3 AWS Lambda 프로젝트 만들어보기
자습서: AWS Lambda 함수 생성, 업로드, 호출 방법


1.4 AWS 자격 증명 설정 
AWS Toolkit for Eclipse를 통해 Amazon Web Services에 액세스하려면 AWS 계정 자격 증명으로 AWS Toolkit for Eclipse를 구성해야 합니다.
AWS 자격 증명 설정

DynamoDB를 이용한 백엔드 구축하기
1. Amazon DynamoDB란?
•	Amazon DynamoDB는 어떤 규모에서도 10밀리초 미만의 성능을 제공하는 키-값 및 문서 데이터베이스입니다.
o	DynamoDB는 유연한 스키마를 가지므로 어느 시점에서든 각 행은 개수와 상관없이 열을 포함할 수 있습니다. 따라서 관계형 데이터베이스에서처럼 테이블 스키마를 재정의할 필요 없이 비즈니스 요구사항이 변경되면 테이블을 쉽게 조정할 수 있습니다.
•	완전관리형의 내구성이 뛰어난 다중 리전, 다중 마스터 데이터베이스로서, 인터넷 규모 애플리케이션을 위한 보안, 백업 및 복원, 인 메모리 캐싱 기능을 기본적으로 제공합니다.

1.1 DynamoDB 핵심 구성 요소
다음은 기본 DynamoDB 구성 요소입니다.
•	테이블 – 다른 데이터베이스 시스템과 마찬가지로 DynamoDB는 데이터를 테이블에 저장합니다. 테이블은 데이터의 집합입니다. 예를 들어, 친구, 가족 또는 기타 관심 있는 사람에 대한 정보를 저장하는 데 사용할 수 있는 People이라는 예제 테이블을 살펴 봅니다. 또한 Cars 테이블에 사람들이 운전하는 차량에 대한 정보를 저장할 수도 있습니다.
•	항목 – 각 테이블에는 0개 이상의 항목이 있습니다. 항목은 모든 기타 항목 중에서 고유하게 식별할 수 있는 속성들의 집합입니다. People 테이블에서 각 항목은 한 사람을 나타냅니다. Cars 테이블의 경우 각 항목은 차량 한 대를 나타냅니다. DynamoDB의 항목은 여러 가지 면에서 다른 데이터베이스 시스템의 행, 레코드 또는 튜플과 유사합니다. DynamoDB에서는 테이블에 저장할 수 있는 항목의 수에 제한이 없습니다.
•	속성 – 각 항목은 하나 이상의 속성으로 구성됩니다. 속성은 기본적인 데이터 요소로서 더 이상 나뉠 필요가 없는 것입니다. 예를 들어 People 테이블의 항목에는 PersonID, LastName, FirstName 등의 속성이 있습니다. Department 테이블의 경우 항목에 DepartmentID, Name, Manager 등의 속성이 있을 수 있습니다. DynamoDB의 속성은 여러 가지 면에서 다른 데이터베이스 시스템의 필드 또는 열과 유사합니다.




 Java를 이용한 Amazon DynamoDB 실습
2.1 Eclipse 용 AWS Toolkit에서 DynamoDB 샘플 코드 실행해보기
•	사전준비
o	Amazon Web Services 계정 준비
o	Eclipse 와 AWS Toolkit for Eclipse를 다운로드하여 설치합니다.
o	AWS Toolkit for Eclipse에 AWS 액세스 키 추가
1.	Eclipse를 시작하고 Eclipse 메뉴에서 파일, 새로 만들기, 기타를 차례대로 선택합니다.
2.	Select a wizard에서 AWS, AWS Java Project, Next를 차례대로 선택합니다.
3.	Create an AWS Java project에서 다음을 수행합니다.
o	프로젝트 이름에 프로젝트 이름(DynamoDBSample)을 입력합니다.
o	Select Account의 목록에서 자격 증명 프로필을 선택합니다.
	AWS Toolkit for Eclipse를 처음 사용하는 경우, Configure AWS Accounts(AWS 계정 구성)를 선택하여 AWS 자격 증명을 설정합니다.
o	Amazon DynamoDB Sample의 체크박스를 선택합니다.
4.	프로젝트를 생성하려면 Finish를 선택합니다.
 
5.	프로그램을 컴파일하고 실행합니다.
2.2 Java와 DynamoDB를 사용하는 AWS Lambda 함수 구현하기
•	이번 실습은 입력으로 주어진 Person 데이터를 DynamoDB에 저장하는 Lambda 함수를 Java를 통해 구현하는 방법을 실습합니다.
•	Person 데이터 형식
•	{
•	    "id": 1,
•	    "firstName": "Kwanwoo"
•	    "lastName": "Lee"
•	    "age":40
}
2.2.1 사전준비
•	Amazon Web Services 계정 준비
•	Eclipse 와 AWS Toolkit for Eclipse를 다운로드하여 설치합니다.
2.2.2 DynamoDB 테이블 생성
•	다음 단계에 따라 People 테이블을 생성합니다.
1.	AWS Management 콘솔에 로그인하고 https://console.aws.amazon.com/dynamodb/에서 DynamoDB 콘솔을 엽니다.
2.	콘솔 왼쪽의 탐색 창에서 [대시보드]를 선택합니다.
3.	콘솔의 오른쪽에서 [테이블 만들기]을 선택합니다.
4.	다음과 같이 테이블 세부 정보를 입력합니다.
	테이블 이름에 People을 입력합니다.
	파티션 키에 id를 입력합니다. 데이터유형은 번호를 선택합니다.
5.	[생성]을 선택하여 테이블을 생성합니다.
2.2.3 Lambda 함수 생성
1.	AWS Lambda Java 프로젝트를 Eclipse용 AWS Toolkit을 이용하여 생성한다.
o	Project name: DynamoDBLambdaJavaProject
o	Group ID: com.example.lambda
o	Artifact ID: dynamodbdemo
o	Class Name: PuttingPersonHandler
o	Input Type에서 Custom을 선택합니다.
2.	Finish 버튼을 클릭합니다.
3.	Eclipse 프로젝트 탐색기를 사용하여 DynamoDBLambdaJavaProject 프로젝트에서 PuttingPersonHandler.java를 열고, 다음 코드로 바꿉니다.
4.	import com.amazonaws.services.dynamodbv2.AmazonDynamoDB;
5.	import com.amazonaws.services.dynamodbv2.AmazonDynamoDBClientBuilder;
6.	import com.amazonaws.services.dynamodbv2.document.DynamoDB;
7.	import com.amazonaws.services.dynamodbv2.document.Item;
8.	import com.amazonaws.services.dynamodbv2.document.PutItemOutcome;
9.	import com.amazonaws.services.dynamodbv2.document.spec.PutItemSpec;
10.	import com.amazonaws.services.dynamodbv2.model.ConditionalCheckFailedException;
11.	import com.amazonaws.services.lambda.runtime.Context;
12.	import com.amazonaws.services.lambda.runtime.RequestHandler;
13.	
14.	public class PuttingPersonHandler implements RequestHandler<Person, String> {
15.	    private DynamoDB dynamoDb;
16.	    private String TABLE_NAME = "People";
17.	    private String REGION = "us-east-1”;
18.	
19.	    @Override
20.	    public String handleRequest(Person input, Context context) {
21.	        this.initDynamoDbClient();
22.	
23.	        putData(input);
24.	        return "Saved Successfully!!";
25.	    }
26.	
27.	    private void initDynamoDbClient() {
28.	        AmazonDynamoDB client = AmazonDynamoDBClientBuilder.standard()
29.	                .withRegion(REGION).build();
30.	         this.dynamoDb = new DynamoDB(client);
31.	    }
32.	
33.	    private PutItemOutcome putData(Person person) 
34.	              throws ConditionalCheckFailedException {
35.	                return this.dynamoDb.getTable(TABLE_NAME)
36.	                  .putItem(
37.	                    new PutItemSpec().withItem(new Item()
38.	                            .withPrimaryKey("id",person.id)
39.	                            .withString("firstName", person.firstName)
40.	                            .withString("lastName", person.lastName)));
41.	            }
42.	}
43.	
44.	class Person {
45.	    public String firstName;
46.	    public String lastName;
47.	    public int id;
48.	}
1.	Lambda에 함수를 업로드하려면, Eclipse 코드 창에서 마우스 오른쪽 버튼을 클릭하고 [AWS Lambda]와 [Upload function to AWS Lambda]를 차례대로 선택합니다.
49.	[Select Target Lambda Function] 페이지에서 사용할 AWS 리전을 선택합니다. 이 리전은 Amazon S3 버킷에 대해 선택한 리전과 동일해야 합니다.
50.	새 Lambda 함수 생성을 선택하고 함수 이름(예: PuttingPersonFunction)을 입력합니다.
51.	[Next]를 선택합니다.
52.	함수 구성 페이지에서 대상 Lambda 함수에 대한 설명을 입력하고 함수에서 사용할 IAM 역할 선택합니다.
o	선택할 IAM 역할에는 dynamoDB에 대한 접근 권한이 설정되어 있어야 합니다.
53.	Lambda 함수에 대해 새로운 Amazon S3 버킷을 생성하고 싶은 경우에는 함수 구성 페이지로 이동하여 함수 코드에 대한 S3 버킷 섹션에서 생성을 선택합니다. 버킷 생성 대화 상자에 버킷 이름을 입력합니다.
54.	Finish를 선택하여 Lambda 함수를 AWS에 업로드합니다.
55.	Lambda 함수를 호출하려면, Eclipse 코드 창에서 마우스 오른쪽 버튼을 클릭하고 AWS Lambda를 선택한 후 Run Function on AWS Lambda(AWS Lambda에서 함수 실행)를 선택합니다.
56.	입력 상자에서 아래와 같은 JSON 문자열을 입력합니다.
57.	{
58.	  "id": 1,
59.	  "firstName": "Kwawnoo",
60.	  "lastName": "Lee"
}
61.	Invoke를 선택하여 Lambda 함수에 입력 데이터를 전송합니다.
62.	결과를 확인하기 위해서는, DynamoDB 콘솔로 이동합니다.
o	콘솔 왼쪽의 탐색 창에서 [테이블]를 선택합니다.
o	오른쪽 창에서 People 테이블을 선택합니다.
o	항목 탭에서 새로운 항목이 추가되었는지 확인합니다.




















DynamoDB와 AWS Lambda를 이용한 IoT Data 저장 백엔드 구축 실습 (수정)
1.	데이터를 저장할 테이블을 파티션 키와 정렬 키로 구성하게 함으로써, 데이블에 저장된 항목을 정렬 키로 정렬 시킬 수 있게 한다.
o	[주의] 파티션 키로만 구성된 테이블은 항목의 검색결과를 정렬된 형태로 얻을 수 없다. 따라서 특정한 키 값을 바탕으로 항목을 정렬시키기 위해서는 테이블을 파티션 키와 정렬 키로 구성된 복합키로 구성해야 한다.
2.	디바이스로부터 수신된 모든 정보를 테이블에 저장하지 않고, 이전에 수신된 정보와 차이가 나는 경우에만 테이블에 저장하도록 수정한다.
o	디바이스에서 측정된 디바이스 상태 값을 주기적으로 AWS IoT로 전송하는데, 이 상태 값의 변화가 매우 적은 경우에는 테이블에 중복된 데이터가 많이 저장된다. 따라서 이를 개선하기 위해서는 이전 값과 차이가 나는 정보만 저장하도록 하는 것이 좀더 효율적이다.
3.	DB 테이블에 정보를 저장하는 규칙(LoggingRule)을 독립적인 규칙으로 분리하여, 해당 규칙을 필요에 따라서 활성화 혹은 비활성화 시킬 수 있도록 수정한다.
o	독립적으로 분리된 정보저장 규칙(LoggingRule)은 필요에 따라서 애플리케이션에서 활성화 및 비활성화를 제어할 수 있다. 이를 통해서 디바이스로부터 수신된 정보를 저장하는 기능을 필요에 따라서 제어할 수 있는 기반이 된다.
•	이상의 개선 사항을 반영한 아키텍처는 다음과 같다.
•	IoT 서비스 아키텍처  
________________________________________


1단계: 역할 설정
AWS 에서 [서비스] – [IAM]을 접속합니다. 왼쪽 카테고리 창에 [역할] 클릭합니다.
[역할 만들기]를 클릭합니다.
[신뢰할 수 있는 유형의 개체 선택]에 [AWS 서비스]를 선택하고
[이 역할을 사용할 서비스 선택]에서 [lambda]를 선탣합니다. 그리고 [다음: 권한]을 클릭합니다.
정책 필터 검색창에 AmazonDynamoDBFullAccess를 검색하고 네모박스를 클릭 선택후 [다음: 태그]합니다.
키-값은 무시하고 [다음: 검토]를 클릭합니다.
역할 이름에 [dynamodb]를 입력 – [역할 만들기]를 클릭하여 역할 만들기를 완성합니다.

2단계: DynamoDB 테이블 만들기
다음 단계에 따라 Waterlevel 테이블을 생성합니다.
1.	AWS Management 콘솔에 로그인하고 https://console.aws.amazon.com/dynamodb/에서 DynamoDB 콘솔을 엽니다.
2.	콘솔 왼쪽의 탐색 창에서 [대시보드]를 선택합니다.
3.	콘솔의 오른쪽에서 [테이블 만들기]을 선택합니다.
4.	다음과 같이 테이블 세부 정보를 입력합니다.
o	테이블 이름에 Waterlevel을 입력합니다.
o	파티션 키에 deviceId를 입력합니다. 데이터유형은 문자열을 선택합니다.
o	정렬 키 추가 체크박스를 선택합니다.
o	정렬 키에 time을 입력합니다. 데이터유형은 번호를 선택합니다.
5.	[생성]을 선택하여 테이블을 생성합니다.

3단계: Lambda 함수 정의
1.	AWS Lambda 프로젝트를 Eclipse용 AWS Toolkit을 이용하여 생성한다.
o	Project name: Waterlevel
o	Group ID: com.example.lambda
o	Artifact ID: recording
o	Class Name: RecordingDeviceInfoHandler2
o	Input Type에서 Custom을 선택합니다.
2.	Finish 버튼을 클릭합니다.
3.	Eclipse 프로젝트 탐색기를 사용하여 RecordingDeviceDataLambdaJavaProject2 프로젝트에서 RecordingDeviceInfoHandler2.java를 열고, 다음 코드로 바꿉니다.


package com.example.lambda.recording;

import java.text.SimpleDateFormat;
import java.util.TimeZone;
import com.amazonaws.services.dynamodbv2.AmazonDynamoDB;
import com.amazonaws.services.dynamodbv2.AmazonDynamoDBClientBuilder;
import com.amazonaws.services.dynamodbv2.document.DynamoDB;
import com.amazonaws.services.dynamodbv2.document.Item;
import com.amazonaws.services.dynamodbv2.document.spec.PutItemSpec;
import com.amazonaws.services.dynamodbv2.model.ConditionalCheckFailedException;
import com.amazonaws.services.lambda.runtime.Context;
import com.amazonaws.services.lambda.runtime.RequestHandler;

public class RecordingDeviceInfoHandler2 implements RequestHandler<Document, String> {

	 private DynamoDB dynamoDb;
	    private String DYNAMODB_TABLE_NAME = "waterleveldb2";

	    @Override
	    public String handleRequest(Document input, Context context) {
	        this.initDynamoDbClient();
	        context.getLogger().log("Input: " + input);

	        //return null;
	        return persistData(input);
	    }

	    private String persistData(Document document) throws ConditionalCheckFailedException {

	        // Epoch Conversion Code: https://www.epochconverter.com/
	        SimpleDateFormat sdf = new SimpleDateFormat ( "yyyy-MM-dd HH:mm:ss");
	        sdf.setTimeZone(TimeZone.getTimeZone("Asia/Seoul"));
	        String timeString = sdf.format(new java.util.Date (document.timestamp*1000));

	        // temperature와 LED 값이 이전상태와 동일한 경우 테이블에 저장하지 않고 종료 
	        if (document.current.state.reported.WaterLevel.equals(document.previous.state.reported.WaterLevel) && 
	                document.current.state.reported.LED.equals(document.previous.state.reported.LED) && 
	                document.current.state.reported.LED2.equals(document.previous.state.reported.LED2) && 
	                document.current.state.reported.LED3.equals(document.previous.state.reported.LED3)) {
	                return null;
	        }

	        return this.dynamoDb.getTable(DYNAMODB_TABLE_NAME)
	                .putItem(new PutItemSpec().withItem(new Item().withPrimaryKey("deviceId", document.device)
	                        .withLong("time", document.timestamp)
	                        .withString("WaterLevel", document.current.state.reported.WaterLevel)
	                        .withString("ledRed", document.current.state.reported.LED)
	                        .withString("ledYellow", document.current.state.reported.LED2)
	                        .withString("ledGreen", document.current.state.reported.LED3)
	                        .withString("timestamp",timeString)))
	                .toString();
	    }

	    private void initDynamoDbClient() {
	        AmazonDynamoDB client = AmazonDynamoDBClientBuilder.standard().withRegion("us-east-1").build();

	        this.dynamoDb = new DynamoDB(client);
	    }

	}

	/**
	 * AWS IoT은(는) 섀도우 업데이트가 성공적으로 완료될 때마다 /update/documents 주제에 다음 상태문서를 게시합니다
	 * JSON 형식의 상태문서는 2개의 기본 노드를 포함합니다. previous 및 current. 
	 * previous 노드에는 업데이트가 수행되기 전의 전체 섀도우 문서의 내용이 포함되고, 
	 * current에는 업데이트가 성공적으로 적용된 후의 전체 섀도우 문서가 포함됩니다. 
	 * 섀도우가 처음 업데이트(생성)되면 previous 노드에는 null이 포함됩니다.
	 * 
	 * timestamp는 상태문서가 생성된 시간 정보이고, 
	 * device는 상태문서에 포함된 값은 아니고, Iot규칙을 통해서 Lambda함수로 전달된 값이다. 
	 * 이 값을 해당 규칙과 관련된 사물이름을 나타낸다. 
	 */
	class Document {
	    public Thing previous;       
	    public Thing current;
	    public long timestamp;
	    public String device;       // AWS IoT에 등록된 사물 이름 
	}

	class Thing {
	    public State state = new State();
	    public long timestamp;
	    public String clientToken;

	    public class State {
	        public Tag reported = new Tag();
	        public Tag desired = new Tag();

	        public class Tag {
	            public String WaterLevel;
	            public String LED;
	            public String LED2;
	            public String LED3;
	        }
	    }
	}

4.	Lambda에 함수를 업로드하려면, Eclipse 코드 창에서 마우스 오른쪽 버튼을 클릭하고 [AWS Lambda]와 [Upload function to AWS Lambda]를 차례대로 선택합니다.
5.	[Select Target Lambda Function] 페이지에서 사용할 AWS 리전을 선택합니다. 이 리전은 Amazon S3 버킷에 대해 선택한 리전과 동일해야 합니다.
6.	새 Lambda 함수 생성을 선택하고 함수 이름(예: WaterlevelDeviceInfoFunction)을 입력합니다.
7.	[Next]를 선택합니다.
8.	함수 구성 페이지에서 대상 Lambda 함수에 대한 설명을 입력하고 함수에서 사용할 IAM 역할 선택합니다.
o	선택할 IAM 역할에는 dynamoDB에 대한 접근 권한이 설정되어 있어야 합니다.(dynamodb)
9.	Lambda 함수에 대해 새로운 Amazon S3 버킷을 생성하고 싶은 경우에는 함수 구성 페이지로 이동하여 함수 코드에 대한 S3 버킷 섹션에서 생성을 선택합니다. 버킷 생성 대화 상자에 버킷 이름을 입력합니다.
10.	Finish를 선택하여 Lambda 함수를 AWS에 업로드합니다.







4단계: IoT 규칙 설정
1.	AWS IoT 콘솔로 이동하여 탐색 창에서 Act (액트)을 선택합니다.
2.	새로운 규칙을 생성하기 위해 생성을 클릭합니다.
3.	이름에 waterleveldbact을 입력합니다.
4.	규칙 쿼리 설명문에 다음을 입력합니다.
SELECT *, 'MyMKRWiFi1010' as device FROM '$aws/things/MyMKRWiFi1010/shadow/update/documents'
o	'$aws/things/MyMKRWiFi1010/shadow/update/documents' 주제로 전송된 메시지가 규칙을 트리거하고, 이 때 전달된 메시지의 모든 항목과 함께 항목 값이 MyMKRWiFi1010인 device 항목을 규칙에 설정된 작업의 입력값으로 전달한다.
o	[가정]: 위 규칙 쿼리는 사물이름이 MyMKRWiFi1010인 경우이고, 사물이름이 다른경우에는 이을 본인이 만든 사물이름으로 변경해야 합니다.
5.	작업 추가를 선택합니다.
6.	작업 선택 아래에서 Send a message to a Lambda function(메시지를 Lambda 함수로 전송)을 선택한 다음 작업 구성을 선택합니다.
7.	선택을 클릭하고, Lambda 함수(WaterlevelDeviceInfoFunction)를 선택합니다.
8.	작업 추가를 선택합니다.

5단계: 깃허브에 올린 Waterlevel 아두이노코드를 업로드후 DynamoDB에 데이터가 쌓이는지 확인해 봅니다.

같은 방법으로 waterdoor DB도 만들어주고 waterdoor 아두이노로 서보모터 2개의 상태도 
데이터가 쌓이는지 확인해 봅니다.


가.	디바이스 로그 조회 REST API 구축하기
1. 디바이스 로그 조회 REST API 구축하기
•	API 요청
GET /devices/{deviceId}/log?from=1000&to=2000
•	응답모델
•	{
•	    "data":[
•	        {
•	            "time":timestamp,
•	            "attributes": {
•	                "attribute1": integer3,
•	                "attribute2": "string3",
•	                ...
•	            }
•	        },
•	        ...
•	    ]
}
1단계: AWS Toolkit을 통해 Lambda 함수 생성
1.	다음 정보를 바탕으로 AWS Lambda 프로젝트를 Eclipse용 AWS Toolkit을 이용하여 생성한다.
o	Project name: LogDeviceLambdaJavaProject
o	Class Name: LogDeviceHandler
o	Input Type에서 Custom을 선택합니다.
2.	Eclipse 프로젝트 탐색기를 사용하여 LogDeviceLambdaJavaProject 프로젝트에서 LogDeviceHandler.java를 열고, 다음 코드로 바꿉니다.
3.	import java.text.ParseException;
4.	import java.text.SimpleDateFormat;
5.	import java.util.Iterator;
6.	import java.util.TimeZone;
7.	
8.	import com.amazonaws.services.dynamodbv2.AmazonDynamoDB;
9.	import com.amazonaws.services.dynamodbv2.AmazonDynamoDBClientBuilder;
10.	import com.amazonaws.services.dynamodbv2.document.DynamoDB;
11.	import com.amazonaws.services.dynamodbv2.document.Item;
12.	import com.amazonaws.services.dynamodbv2.document.ItemCollection;
13.	import com.amazonaws.services.dynamodbv2.document.QueryOutcome;
14.	import com.amazonaws.services.dynamodbv2.document.Table;
15.	import com.amazonaws.services.dynamodbv2.document.spec.QuerySpec;
16.	import com.amazonaws.services.dynamodbv2.document.utils.NameMap;
17.	import com.amazonaws.services.dynamodbv2.document.utils.ValueMap;
18.	import com.amazonaws.services.lambda.runtime.Context;
19.	import com.amazonaws.services.lambda.runtime.RequestHandler;
20.	
21.	public class LogDeviceHandler implements RequestHandler<Event, String> {
22.	
23.	    private DynamoDB dynamoDb;
24.	    private String DYNAMODB_TABLE_NAME = "waterleveldb2";
25.	
26.	    @Override
27.	    public String handleRequest(Event input, Context context) {
28.	        this.initDynamoDbClient();
29.	
30.	        Table table = dynamoDb.getTable(DYNAMODB_TABLE_NAME);
31.	
32.	        long from=0;
33.	        long to=0;
34.	        try {
35.	            SimpleDateFormat sdf = new SimpleDateFormat ( "yyyy-MM-dd HH:mm:ss");
36.	            sdf.setTimeZone(TimeZone.getTimeZone("Asia/Seoul"));
37.	
38.	            from = sdf.parse(input.from).getTime() / 1000;
39.	            to = sdf.parse(input.to).getTime() / 1000;
40.	        } catch (ParseException e1) {
41.	            e1.printStackTrace();
42.	        }
43.	
44.	        QuerySpec querySpec = new QuerySpec()
45.	                .withKeyConditionExpression("deviceId = :v_id and #t between :from and :to")
46.	                .withNameMap(new NameMap().with("#t", "time"))
47.	                .withValueMap(new ValueMap().withString(":v_id",input.device).withNumber(":from", from).withNumber(":to", to)); 
48.	
49.	        ItemCollection<QueryOutcome> items=null;
50.	        try {           
51.	            items = table.query(querySpec);
52.	        }
53.	        catch (Exception e) {
54.	            System.err.println("Unable to scan the table:");
55.	            System.err.println(e.getMessage());
56.	        }
57.	
58.	        return getResponse(items);
59.	    }
60.	
61.	    private String getResponse(ItemCollection<QueryOutcome> items) {
62.	
63.	        Iterator<Item> iter = items.iterator();
64.	        String response = "{ \"data\": [";
65.	        for (int i =0; iter.hasNext(); i++) {
66.	            if (i!=0) 
67.	                response +=",";
68.	            response += iter.next().toJSON();
69.	        }
70.	        response += "]}";
71.	        return response;
72.	    }
73.	
74.	    private void initDynamoDbClient() {
75.	        AmazonDynamoDB client = AmazonDynamoDBClientBuilder.standard().build();
76.	
77.	        this.dynamoDb = new DynamoDB(client);
78.	    }
79.	}
80.	
81.	class Event {
82.	    public String device;
83.	    public String from;
84.	    public String to;
}
85.	Lambda에 함수를 업로드하려면, Eclipse 코드 창에서 마우스 오른쪽 버튼을 클릭하고 [AWS Lambda]와 [Upload function to AWS Lambda]를 차례대로 선택합니다.
86.	[Select Target Lambda Function] 페이지에서 사용할 AWS 리전을 선택합니다. 이 리전은 Amazon S3 버킷에 대해 선택한 리전과 동일해야 합니다.
87.	새 Lambda 함수 생성을 선택하고 함수 이름(예: WaterDeviceFunction)을 입력한 후, [Next]를 선택합니다.
88.	함수 구성Function Configuration 페이지에서 대상 Lambda 함수에 대한 설명을 입력하고 함수에서 사용할 IAM 역할 선택합니다.
o	사용할 역할은 AmazonDynamoDBFullAccess 정책이 연결되어 있어야 합니다. 만약 이러한 역할이 없다면, IAM 콘솔을 통해 해당 역할을 생성합니다.
	다음 링크를 통해 역할 생성에 대해서 자세히 살펴보세요.
89.	Lambda 함수 코드를 저장할 S3 버킷을 선택합니다. 만약 새로운 Amazon S3 버킷을 생성하고 싶은 경우에는 생성 버튼을 클릭하고 버킷 생성 대화 상자에 버킷 이름을 입력합니다.
90.	Finish를 선택하여 Lambda 함수를 AWS에 업로드합니다.
91.	Lambda 함수를 실행하려면, Eclipse 코드 창에서 마우스 오른쪽 버튼을 클릭하고 AWS Lambda를 선택한 후 Run Function on AWS Lambda(AWS Lambda에서 함수 실행)를 선택합니다.
92.	Enter the JSON input for your function이 선택된 상태에서 입력 창에 다음 입력 문자열을 입력한다.
o	device 속성: 조회할 사물의 이름이 MyMKRWiFi1010인 경우를 가정
o	from 속성: 시작 시간 (yyyy-MM-dd hh:mm:ss) 형식의 문자열
o	to 속성: 종료 시간 (yyyy-MM-dd hh:mm:ss) 형식의 문자열
{ "device": "MyMKRWiFi1010", "from":"2019-12-10 17:56:26", "to": "2019-12-30 18:56:26"} 
93.	Invoke 버튼을 클릭한 후, Eclipse Console 창에 다음과 같은 결과가 출력되는 지 확인합니다.

2단계: API Gateway 콘솔에서 REST API 생성

1.	API Gateway 콘솔로 이동합니다.
2.	이전에 생성한 my-device-api를 선택합니다.
3.	리소스 이름(/{device})을 선택합니다.
4.	작업 드롭다운 메뉴에서 리소스 생성을 선택합니다.
5.	리소스 이름에 log를 입력하고, 리소스 생성을 클릭합니다.
6.	작업 드롭다운 메뉴에서 메소드 생성을 선택합니다.
7.	리소스 이름 (/log) 아래에 드롭다운 메뉴가 보일 것입니다. GET을 선택한 후 확인 표시 아이콘(체크)을 선택하여 선택 사항을 저장합니다.
8.	/devices/{device}/log – GET – 설정 창의 통합 유형에서 Lambda 함수를 선택합니다.
9.	Lambda 프록시 통합 사용 상자를 선택하지 않은 상태로 놔둡니다.
10.	Lambda 리전에서 Lambda 함수를 생성한 리전을 선택합니다.
11.	Lambda 함수 필드에 문자를 입력한 후 드롭다운 메뉴에서 WaterDeviceFunction 을 선택합니다. 저장을 선택하여 선택 사항을 저장합니다
12.	Lambda 함수에 대한 권한 추가 팝업이 나타나면(Lambda 함수를 호출하기 위해 API Gateway에 권한을 부여하려고 합니다....”), 확인을 선택하여 API Gateway에 해당 권한을 부여합니다.
o	이제 /devices/{device}/log – GET – 메소드 실행 창이 보일 것입니다.
다음 단계는 API Gateway를 통해 들어오는 클라이언트의 입력을 Lambda 함수에 전달하기 위해서 클라이언트의 입력을 Lambda 함수의 입력으로 매핑하는 과정에 대해서 진행합니다.
1.	메서드 실행 창에서 메서드 요청을 선택합니다.
2.	URL 쿼리 문자열 파라미터(URL Query String Parameters) 섹션을 확장합니다.
o	쿼리 문자열 추가(Add query string)를 선택합니다. 이름에 from을 입력합니다. 필수 옵션을 선택하고 확인 표시 아이콘을 선택하여 설정을 저장합니다. 캐싱(Caching)을 비워두어 이 연습에 불필요한 요금 부과를 방지합니다.
o	쿼리 문자열 추가(Add query string)를 선택합니다. 이름에 to을 입력하고, 이전과 동일한 과정을 진행합니다.
3.	/log GET 메서드를 선택하고 통합 요청(Integration Request)을 선택하여 본문 매핑 템플릿을 설정합니다.
1.	매핑 템플릿(Mapping Templates) 섹션을 확장합니다. 매핑 템플릿 추가(Add mapping template)를 선택합니다. Content-Type에 application/json을 입력합니다. 확인 표시 아이콘을 선택하여 설정을 저장합니다.
	나타나는 팝업에서 예, 이 통합 보호(Yes, secure this integration)를 선택합니다.
2.	요청 본문 패스스루(Request body passthrough)에 권장되는 정의된 템플릿이 없는 경우(권장)를 선택합니다.
3.	매핑 템플릿 편집기에 다음 매핑 스크립트를 입력합니다.
4.	{
5.	  "device": "$input.params('device')",
6.	  "from": "$input.params('from')",
7.	  "to":  "$input.params('to')"
}
8.	저장을 선택합니다.
4.	/devices/{device}/log – GET – 메소드 실행 창으로 이동하여, 클라이언트 부분의 테스트를 클릭합니다.
5.	1단계에서 Lambda 함수를 만든 방법에 따라 다음과 같이 수행합니다.
o	방법1을 사용한 경우: {device} 경로에 본인이 만든 사물의 로그 데이터를 기록하는 DynamoDB 테이블 이름(예, DeviceData)을 입력합니다.
o	방법2를 사용한 경우: {device} 경로에 본인이 만든 사물 이름(예, MyMKRWiFi1010)을 입력합니다.
6.	쿼리 문자열에 아래와 같은 내용을 입력합니다.
from="2019-12-10 00:00:00"&to="2019-12-30 18:09:36"
7.	테스트버튼을 클릭하여 다음과 같은 결과가 나오는 지 확인합니다.
주소창에 넣을때는 from=2019-12-10 00:00:00&to=2019-12-30 18:09:36
위와 같이 “따옴표를 지워줘야합니다.
 







2. 디바이스 상태변경 REST API 구축하기
API 요청
PUT /devices/{deviceID}
•	payload
•	{ 
•	    "tags" : [
•	        {
•	            "attrName": "motor",
•	            "attrValue": "UP"
•	        },
•	        {
•	            "attrName": "motora",
•	            "attrValue": "down"
•	        }
•	    ]
}

1단계: AWS Toolkit을 통해 Lambda 함수 생성
1.	다음 정보를 바탕으로 AWS Lambda 프로젝트를 Eclipse용 AWS Toolkit을 이용하여 생성한다.
o	Project name: UpdateDeviceLambdaJavaProject
o	Class Name: UpdateDeviceHandler
o	Input Type에서 Custom을 선택합니다.
2.	생성된 UpdateDeviceLambdaJavaProject의 pom.xml 파일을 열고, <dependencies> 태그 안에 aws-java-sdk-iot에 대한 의존성을 추가한 후에, 파일을 저장합니다.
3.	  <dependencies>
4.	    ...    
5.	    <dependency>
6.	      <groupId>com.amazonaws</groupId>
7.	      <artifactId>aws-java-sdk-iot</artifactId>
8.	    </dependency>
9.	
</dependencies>
10.	Eclipse 프로젝트 탐색기를 사용하여 UpdateDeviceLambdaJavaProject 프로젝트에서 UpdateDeviceHandler.java를 열고, 다음 코드로 바꿉니다.

1.	import java.nio.ByteBuffer;
2.	import java.util.ArrayList;
3.	
4.	import com.amazonaws.services.iotdata.AWSIotData;
5.	import com.amazonaws.services.iotdata.AWSIotDataClientBuilder;
6.	import com.amazonaws.services.iotdata.model.UpdateThingShadowRequest;
7.	import com.amazonaws.services.iotdata.model.UpdateThingShadowResult;
8.	import com.amazonaws.services.lambda.runtime.Context;
9.	import com.amazonaws.services.lambda.runtime.RequestHandler;
10.	import com.fasterxml.jackson.annotation.JsonCreator;
11.	
12.	public class UpdateDeviceHandler implements RequestHandler<Event, String> {
13.	
14.	    @Override
15.	    public String handleRequest(Event event, Context context) {
16.	        context.getLogger().log("Input: " + event);
17.	
18.	        AWSIotData iotData = AWSIotDataClientBuilder.standard().build();
19.	
20.	        String payload = getPayload(event.tags);
21.	
22.	        UpdateThingShadowRequest updateThingShadowRequest  = 
23.	                new UpdateThingShadowRequest()
24.	                    .withThingName(event.device)
25.	                    .withPayload(ByteBuffer.wrap(payload.getBytes()));
26.	
27.	        UpdateThingShadowResult result = iotData.updateThingShadow(updateThingShadowRequest);
28.	        byte[] bytes = new byte[result.getPayload().remaining()];
29.	        result.getPayload().get(bytes);
30.	        String resultString = new String(bytes);
31.	        return resultString;
32.	    }
33.	
34.	    private String getPayload(ArrayList<Tag> tags) {
35.	        String tagstr = "";
36.	        for (int i=0; i < tags.size(); i++) {
37.	            if (i !=  0) tagstr += ", ";
38.	            tagstr += String.format("\"%s\" : \"%s\"", tags.get(i).tagName, tags.get(i).tagValue);
39.	        }
40.	        return String.format("{ \"state\": { \"desired\": { %s } } }", tagstr);
41.	    }
42.	
43.	}
44.	
45.	class Event {
46.	    public String device;
47.	    public ArrayList<Tag> tags;
48.	
49.	    public Event() {
50.	         tags = new ArrayList<Tag>();
51.	    }
52.	}
53.	
54.	class Tag {
55.	    public String tagName;
56.	    public String tagValue;
57.	
58.	    @JsonCreator 
59.	    public Tag() {
60.	    }
61.	
62.	    public Tag(String n, String v) {
63.	        tagName = n;
64.	        tagValue = v;
65.	    }
66.	}
67.	Lambda에 함수를 업로드하려면, Eclipse 코드 창에서 마우스 오른쪽 버튼을 클릭하고 [AWS Lambda]와 [Upload function to AWS Lambda]를 차례대로 선택합니다.
68.	[Select Target Lambda Function] 페이지에서 사용할 AWS 리전을 선택합니다. 이 리전은 Amazon S3 버킷에 대해 선택한 리전과 동일해야 합니다.
69.	새 Lambda 함수 생성을 선택하고 함수 이름(예: UpdateDeviceFunction)을 입력한 후, [Next]를 선택합니다.
70.	함수 구성(Function Configuration 페이지에서 대상 Lambda 함수에 대한 설명을 입력하고 함수에서 사용할 IAM 역할 선택합니다.
o	사용할 역할은 AWSIoTFullAccess 정책이 연결되어 있어야 합니다. 만약 이러한 역할이 없다면, IAM 콘솔을 통해 해당 역할을 생성합니다.
	다음 링크를 통해 역할 생성에 대해서 자세히 살펴보세요.
71.	Lambda 함수 코드를 저장할 S3 버킷을 선택합니다. 만약 새로운 Amazon S3 버킷을 생성하고 싶은 경우에는 생성 버튼을 클릭하고 버킷 생성 대화 상자에 버킷 이름을 입력합니다.
72.	Finish를 선택하여 Lambda 함수를 AWS에 업로드합니다.
73.	Lambda 함수를 실행하려면, Eclipse 코드 창에서 마우스 오른쪽 버튼을 클릭하고 AWS Lambda를 선택한 후 Run Function on AWS Lambda(AWS Lambda에서 함수 실행)를 선택합니다.
74.	Enter the JSON input for your function이 선택된 상태에서 입력 창에 다음 입력 문자열을 입력한다.
o	조회할 사물의 이름이 MotorMKR인 경우를 가정
o	device 속성: 변경할 사물의 이름
o	tags 속성: 변경할 사물의 태그 객체 배열 (이름과 값으로 정의됨)
o	{
o	    "device": "MotorMKR",
o	    "tags" : [
o	        {
o	            "tagName": "motor",
o	            "tagValue": "UP"
o	        },
o	        {
o	            "tagName": "motora",
o	            "tagValue": "DOWN"
o	        }   
o	    ]
}
75.	Invoke 버튼을 클릭한 후, Eclipse Console 창에 다음과 같은 결과가 출력되는 지 확인합니다.
76.	Invoking function...
77.	==================== FUNCTION OUTPUT ====================
78.	"{\"state\":{\"desired\":{\"motor\":\"UP\",\"motora\":\"DOWN\"}},\"metadata\":{\"desired\":{\" motor \":{\"timestamp\":1575212613},\" motora \":{\"timestamp\":1575212613}}},\"version\":4454,\"timestamp\":1575212613}"
79.	==================== FUNCTION LOG OUTPUT ====================
80.	START RequestId: ffbcd4f1-e3c5-483d-97a3-1c9b4685dd5a Version: $LATEST
81.	Input: com.amazonaws.lambda.demo.Event@6e0e048aEND RequestId: ffbcd4f1-e3c5-483d-97a3-1c9b4685dd5a
REPORT RequestId: ffbcd4f1-e3c5-483d-97a3-1c9b4685dd5a  Duration: 7266.17 ms    Billed Duration: 7300 ms    Memory Size: 512 MB Max Memory Used: 140 MB Init Duration: 382.85 ms    
2단계 API Gateway 콘솔에서 REST API 생성
1.	API Gateway 콘솔로 이동합니다.
2.	이전에 생성한 my-device-api를 선택합니다.
3.	리소스 이름(/{device})을 선택합니다.
4.	작업 드롭다운 메뉴에서 메소드 생성을 선택합니다.
5.	리소스 이름 (/{devices}) 아래에 드롭다운 메뉴가 보일 것입니다. PUT을 선택한 후 확인 표시 아이콘(체크)을 선택하여 선택 사항을 저장합니다.
6.	/devices/{device} – PUT – 설정 창의 통합 유형에서 Lambda 함수를 선택합니다.
7.	Lambda 프록시 통합 사용 상자를 선택하지 않은 상태로 놔둡니다.
8.	Lambda 리전에서 Lambda 함수를 생성한 리전을 선택합니다.
9.	Lambda 함수 필드에 문자를 입력한 후 드롭다운 메뉴에서 UpdateDeviceFunction을 선택합니다. 저장을 선택하여 선택 사항을 저장합니다
10.	Lambda 함수에 대한 권한 추가 팝업이 나타나면(Lambda 함수를 호출하기 위해 API Gateway에 권한을 부여하려고 합니다....”), 확인을 선택하여 API Gateway에 해당 권한을 부여합니다.
o	이제 /devices/{device} – PUT – 메소드 실행 창이 보일 것입니다.
11.	다음 단계는 API Gateway를 통해 들어오는 클라이언트의 입력을 Lambda 함수에 전달하기 위해서 클라이언트의 입력을 Lambda 함수의 입력으로 매핑하는 과정에 대해서 진행합니다.
o	API Gatway에서 모델은 클라이언트의 입력 데이터 구조를 JSON 스키마 draft 4를 사용하여 정의한 것으로서, 이를 이용하여 API Gateway가 클라이언트 입력에 대한 검사 및 SDK 생성에 사용됩니다.
o	모델을 정의하려면 API Gateway 기본 탐색 창에서 API 아래에 있는 모델을 선택한 다음 생성을 선택합니다.
1.	모델 이름에 UpdateDeviceInput을 입력합니다.
2.	콘텐츠 유형에 application/json을 입력합니다.
3.	Model description(모델 설명)은 비워 둡니다.
4.	다음 스키마 정의를 Model schema(모델 스키마) 편집기에 복사합니다.
5.	{
6.	  "$schema": "http://json-schema.org/draft-04/schema#",
7.	  "title": "UpdateDeviceInput",
8.	  "type" : "object",
9.	  "properties" : {
10.	      "tags" : {
11.	          "type": "array",
12.	          "items": {
13.	              "type": "object",
14.	              "properties" : {
15.	                "tagName" : { "type" : "string"},
16.	                "tagValue" : { "type" : "string"}
17.	              }
18.	          }
19.	      }
20.	  }
}
21.	모델 생성을 선택하여 입력 모델 정의를 완료합니다.
22.	리소스를 선택하고 /{device} PUT 메서드를 선택하고 메서드 요청(Method Request)을 선택하고 요청 본문(Request body)을 확장합니다. 모델 추가를 선택합니다. 콘텐츠 유형에 application/json을 입력합니다. 모델 이름에서 UpdateDeviceInput을 선택합니다. 확인 표시 아이콘을 선택하여 설정을 저장합니다.
12.	/{device} PUT 메서드를 선택하고 통합 요청(Integration Request)을 선택하여 본문 매핑 템플릿을 설정합니다.
1.	매핑 템플릿(Mapping Templates) 섹션을 확장합니다. 매핑 템플릿 추가(Add mapping template)를 선택합니다. Content-Type에 application/json을 입력합니다. 확인 표시 아이콘을 선택하여 설정을 저장합니다.
	나타나는 팝업에서 예, 이 통합 보호(Yes, secure this integration)를 선택합니다.
2.	요청 본문 패스스루(Request body passthrough)에 권장되는 정의된 템플릿이 없는 경우(권장)를 선택합니다.
3.	템플릿 생성(Generate template)에서 UpdateDeviceInput을 선택하여 초기 매핑 템플릿을 생성합니다. 이 옵션은 처음부터 매핑 템플릿을 작성할 필요가 없는 모델 스키마를 정의했기 때문에 사용할 수 있습니다.
4.	매핑 템플릿 편집기에 생성된 매핑 스크립트를 다음과 바꿉니다.
5.	#set($inputRoot = $input.path('$'))
6.	{
7.	    "device": "$input.params('device')",
8.	    "tags" : [
9.	    ##TODO: Update this foreach loop to reference array from input json
10.	        #foreach($elem in $inputRoot.tags)
11.	        {
12.	            "tagName" : "$elem.tagName",
13.	            "tagValue" : "$elem.tagValue"
14.	        } 
15.	        #if($foreach.hasNext),#end
16.	        #end
17.	    ]
}
18.	저장을 선택합니다.
13.	/devices/{device} – PUT – 메소드 실행 창으로 이동하여, 클라이언트 부분의 테스트를 클릭합니다.
14.	{device} 경로에 본인이 만든 사물 이름(예, MotorMKR)을 입력합니다.
15.	요청 본문에 아래와 같은 내용을 입력합니다.
16.	{
17.	    "tags" : [
18.	            {
19.	                "tagName": " motor",
20.	                "tagValue": "UP"
21.	            },
22.	            {
23.	                "tagName": " motora",
24.	                "tagValue": "DOWN"
25.	            }   
26.	    ]
}
27.	테스트버튼을 클릭하여 다음과 같은 결과가 나오는 지 확인합니다.

 

 



3단계: CORS 활성환 및 API Gateway 콘솔에서 REST API 배포
REST API 리소스에 대해 CORS 지원 활성화
1.	리소스에서 리소스를 선택합니다. 그렇게 하면 리소스 상의 모든 메서드에 대해 CORS가 활성화됩니다.
2.	작업 드롭다운 메뉴에서 CORS 활성화(Enable CORS)를 선택합니다.
3.	CORS 활성화 및 기존의 CORS 헤더 대체를 선택합니다.
4.	메서드 변경사항 확인 창에서 예, 기존 값을 대체하겠습니다.를 선택합니다.
2단계를 완료하면 API를 생성했지만 아직 실제로 사용할 수는 없습니다. 배포해야 하기 때문입니다.
1.	작업 드롭다운 메뉴에서 Deploy API(API 배포)를 선택합니다.
2.	배포 스테이지 드롭다운 메뉴에서 prod를 선택합니다.
3.	배포을 선택합니다.

지금까지 배포한 주소를 기억하여 저장하고 웹에서 구축할 때 붙혀넣기를 해줄겁니다.


웹 구축하기 

Controller_devices.js 파일의 코드를 가져옵니다. 거기에 자신의 배포한 주소로 바꿔줍니다.
 

List_device.html파일을 만들고 코드를 넣어줍니다.





 

잘 만들어졌습니다.
















